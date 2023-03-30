#pragma once

#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

using std::shared_ptr, std::make_shared;

#include "AbstractFrameStreamConsumer.h"

/**
 * Abstraction for the inputs to a Signal
 */
template <typename frame>
class FrameStreamConsumer : public AbstractFrameStreamConsumer {

private:
public:
  FrameStreamConsumer(AbstractFrameStream *owner, const std::string &name,
                      bool keepSyncedToOwner = true)
      : AbstractFrameStreamConsumer(owner, name, keepSyncedToOwner) {
    setConstant(0);
  }

public:
  std::shared_ptr<FrameStream<frame>> typedConnection() {
    // Hmm seems risky
    return std::dynamic_pointer_cast<FrameStream<frame>>(untypedConnection);
  }

public:
  frame readFrame() {
    checkConnection();
    return typedConnection()->readFrame();
  }

  void connect(std::shared_ptr<FrameStream<frame>> inputSignal) {
    untypedConnection = inputSignal;
  }

public:
  void setConstant(frame k);

  FrameStream<frame> &
  operator<<(std::shared_ptr<FrameStream<frame>> instrument) {
    connect(instrument);
    return *instrument;
  }

  void operator<<(double k) { setConstant(k); }
};

/**
 * This class just exists so that FrameStreamConsumer's don't have to know the
 * frame type of their owners.
 */
class AbstractFrameStream {
  friend AbstractFrameStreamConsumer;

public:
  int internalClock = 0;

protected:
  std::vector<AbstractFrameStreamConsumer *> inputs;

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
  void advanceToNextFrame() {
    ++internalClock;
    syncInputs();
    action();
  }
  void sync(int clock) {
    while (internalClock < clock) {
      advanceToNextFrame();
    }
  }

private:
  void syncInputs() {
    for (auto input : inputs)
      input->syncToOwner();
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
  std::vector<std::shared_ptr<AbstractFrameStream>> inputSignals() const {
    std::vector<std::shared_ptr<AbstractFrameStream>> list;
    for (auto input : inputs) {
      input->checkConnection();
      list.push_back(input->untypedConnection);
    }
    return list;
  }
};

template <typename frame> class FrameStream : public AbstractFrameStream {
protected:
  frame *output;

public:
  FrameStream() { output = new frame; }
  ~FrameStream() { delete output; }

protected:
  /**
   * Update the latest frame.
   */
  void writeFrame(const frame &y) { *output = y; }

public:
  frame operator[](int clock) {
    sync(clock);
    return readFrame();
  }

  frame readFrame() { return *output; }

  frame advanceToNextFrameAndRead() {
    advanceToNextFrame();
    return readFrame();
  }

  AbstractFrameStreamConsumer &defaultInput() {
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
           "] = " + std::to_string(*output);
  }
};

/**
 * Convenient alias for very freqeuent type.
 */
typedef shared_ptr<FrameStream<double>> sigarette;
