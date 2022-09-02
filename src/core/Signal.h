#pragma once

#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

using std::shared_ptr, std::make_shared;

class UntypedSignalInput;
template <typename frame> class SignalInput;
class UntypedSignal;
template <typename frame> class Signal;

class UntypedSignalInput {
  friend UntypedSignal;

protected:
  UntypedSignal *owner;

public:
  UntypedSignalInput(UntypedSignal *owner, const std::string &name);

  virtual void connect(shared_ptr<Signal<double>> signal);

public:
  virtual void setConstant(double k);

  /**
   * Synchronise the plugged instrument with the owner
   */
  void sync(int clock);

protected:
  std::shared_ptr<UntypedSignal> untypedConnection;

public:
  bool hasConnection();

public:
  void reset();
};

/**
 * Abstraction for the inputs to a Signal
 */
template <typename frame> class SignalInput : public UntypedSignalInput {

private:
  frame constant;

public:
  SignalInput(UntypedSignal *owner, const std::string &name)
      : UntypedSignalInput(owner, name), constant(0) {}

public:
  std::shared_ptr<Signal<frame>> typedConnection() {
    // Hmm seems risky
    return std::dynamic_pointer_cast<Signal<frame>>(untypedConnection);
  }

public:
  frame operator()() {
    if (hasConnection()) {
      return (*typedConnection())();
    } else
      return constant;
  }

  void connect(std::shared_ptr<Signal<frame>> inputSignal) {
    untypedConnection = inputSignal;
  }

  void disconnect() { untypedConnection = nullptr; }

public:
  void setConstant(double k) {
    disconnect();
    constant = k;
  }

  Signal<frame> &operator<<(std::shared_ptr<Signal<frame>> instrument) {
    connect(instrument);
    return *instrument;
  }

  void operator<<(double k) { setConstant(k); }

public:
  double currentConstant() {
    if (hasConnection()) {
      std::cerr << "Cannot get constant of non-constant signal input!\n";
      throw 1;
    } else
      return constant;
  }
};

/**
 * This class just exists so that SignalInput's don't have to know the
 * frame type of their owners.
 */
class UntypedSignal {
  friend UntypedSignalInput;

public:
  int internalClock = 0;

protected:
  std::vector<UntypedSignalInput *> inputs;

public:
  virtual std::string label() { return "Signal"; }
  virtual std::string summary() {
    return label() + "@" + std::to_string(internalClock);
  }

public:
  /**
   * Naive instruments work a bit like clock work. Every frame of the digital
   * signal they "tick". What they actually do when they tick is up to them!
   */
  virtual void action() {
    std::cerr
        << "Oh no, looks like the programmer forgot to implement the action "
           "method for "
        << label() << "\n";
    throw 1;
  }

public:
  void sync(int clock) {
    while (internalClock < clock) {
      ++internalClock;
      syncInputs();
      action();
    }
  }

private:
  void syncInputs() {
    for (auto input : inputs)
      input->sync(internalClock);
  }

protected:
  /**
   * Reset the internal state of the Signal. Stateless signals will NOT
   * override this method
   */
  virtual void resetState() {
    // noop
  }

public:
  void reset() {
    // FIXME: Need a circuit breaker for feedback loops
    for (auto input : inputs)
      input->reset();
    resetState();
  }

public:
  std::vector<std::shared_ptr<UntypedSignal>> inputSignals() const {
    std::vector<std::shared_ptr<UntypedSignal>> list;
    for (auto input : inputs)
      if (input->hasConnection())
        list.push_back(input->untypedConnection);
    return list;
  }
};

/**
 * I think its intuitive to think of audio processes like little machines.
 */
template <typename frame> class Signal : public UntypedSignal {
protected:
  frame latestFrame;

protected:
  /**
   * Update the latest frame.
   */
  void out(const frame &y) { latestFrame = y; }

public:
  frame operator[](int clock) {
    sync(clock);
    return latestFrame;
  }

  frame next() {
    sync(internalClock + 1);
    return latestFrame;
  }
  frame operator++() { return next(); }

  frame operator()() { return latestFrame; }

  UntypedSignalInput &defaultInput() {
    if (inputs.size() > 0)
      return *inputs[0];
    else {
      std::cerr << "Trying to get default input but the Signal has no inputs";
      throw 1;
    }
  }

  void operator<<(double k) { defaultInput().setConstant(k); }

public:
  std::string summary() override {
    return label() + "[" + std::to_string(internalClock) +
           "] = " + std::to_string(latestFrame);
  }
};
