#pragma once

#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

class UntypedSignalInput;
template <typename SignalFrame> class SignalInput;
class UntypedSignal;
template <typename SignalFrame> class Signal;

class UntypedSignalInput {
protected:
  UntypedSignal *owner;

public:
  UntypedSignalInput(UntypedSignal *owner) : owner(owner){};

  virtual void connect(Signal<double> *signal) {
    std::cerr << "No override for "
                 "UntypedSignalInput::connect(Signal<double>*) method\n";
    throw 1;
  }

public:
  virtual void setConstant(double k) {
    std::cerr
        << "No override for UntypedSignalInput::setConstant(double) method\n";
    throw 1;
  }

protected:
  UntypedSignal *untypedConnection = nullptr;

public:
  bool hasPlug() { return untypedConnection != nullptr; }
};

/**
 * Abstraction for the inputs to a Signal
 */
template <typename SignalFrame> class SignalInput : public UntypedSignalInput {

private:
  Signal<SignalFrame> *connection;
  SignalFrame constant;

public:
  SignalInput(UntypedSignal *owner)
      : UntypedSignalInput(owner), constant(0), connection(nullptr) {}

  /**
   * Synchronise the plugged instrument with the owner
   */
  SignalFrame sync();

  SignalFrame operator()() { return sync(); }

  void connect(Signal<SignalFrame> *inputSignal) {
    untypedConnection = inputSignal;
    connection = inputSignal;
  }

  void disconnect() {
    connection = nullptr;
    untypedConnection = nullptr;
  }

public:
  void setConstant(double k) {
    disconnect();
    constant = k;
  }

  Signal<SignalFrame> &operator<<(Signal<SignalFrame> *instrument) {
    connect(instrument);
    return *instrument;
  }

  Signal<SignalFrame> &operator<<(Signal<SignalFrame> &instrument) {
    connect(&instrument);
    return instrument;
  }

  void operator<<(double k) { setConstant(k); }

public:
  Signal<SignalFrame> *currentConnection() {
    if (hasPlug())
      return connection;
    else {
      std::cerr << "Cannot get connection of unplugged input!\n";
      throw 1;
    }
  }
  double currentConstant() {
    if (hasPlug()) {
      std::cerr << "Cannot get constant of non-constant signal input!\n";
      throw 1;
    } else
      return constant;
  }
};

/**
 * This class just exists so that SignalInput's don't have to know the
 * SignalFrame type of their owners.
 */
class UntypedSignal {
public:
  int internalClock = 0;

protected:
  std::vector<UntypedSignalInput *> inputs;

protected:
  template <typename SignalFrame>
  SignalInput<SignalFrame> &addInput(double initValue = 0) {
    auto signalInput = new SignalInput<SignalFrame>(this);
    inputs.push_back(signalInput);
    return *signalInput;
  }

public:
  virtual std::string label() { return "Signal"; }
  std::string summary() {
    return label() + "@" + std::to_string(internalClock);
  }

public:
  /**
   * Naive instruments work a bit like clock work. Every frame of the digital
   * signal they "tick". What they actually do when they tick is up to them!
   */
  virtual void action() {
    std::cerr
        << "Oh no, looks like the programmer forgot to implement the tick "
           "method for a Signal\n";
    throw 1;
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
    resetState();
    // TODO: Reset all the inputs too
  }
};

/**
 * I think its intuitive to think of audio processes like little machines.
 */
template <typename SignalFrame> class Signal : public UntypedSignal {
protected:
  SignalFrame latestFrame;

protected:
  /**
   * Update the latest frame.
   */
  void out(const SignalFrame &y) { latestFrame = y; }

public:
  SignalFrame tickUntil(int time) {
    while (internalClock < time) {
      ++internalClock;
      action();
    }
    return latestFrame;
  }

public:
  SignalFrame operator[](int index) { return tickUntil(index); }

  SignalFrame next() { return tickUntil(internalClock + 1); }
  SignalFrame operator++() { return next(); }

  UntypedSignalInput &defaultInput() {
    if (inputs.size() > 0)
      return *inputs[0];
    else {
      std::cerr << "Trying to get default input but the Signal has no inputs";
      throw 1;
    }
  }

  template <typename InputSignalFrame>
  Signal<InputSignalFrame> &operator<<(Signal<InputSignalFrame> &signal) {
    defaultInput().connect(&signal);
    return signal;
  }

  void operator<<(double k) { defaultInput().setConstant(k); }
};
