#pragma once

#include "Signal.h"
#include "UntypedSignalInput.h"
#include <iostream>

/**
 * Abstraction for the inputs to a Signal
 */
template <typename SignalFrame> class SignalInput : public UntypedSignalInput {

  Signal<SignalFrame> *plugged;
  SignalFrame constant;

public:
  SignalInput(UntypedSignal *owner)
      : UntypedSignalInput(owner), constant(0), plugged(nullptr) {}

  /**
   * Synchronise the plugged instrument with the owner
   */
  SignalFrame sync() {
    if (plugged)
      return plugged->tickUntil(owner->internalClock);
    else
      return constant;
  }

  SignalFrame operator()() { return sync(); }

  void connect(Signal<SignalFrame> *instrument) { plugged = instrument; }

  void disconnect() { plugged = nullptr; }

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
  bool hasPlug() { return plugged != nullptr; }
  Signal<double> *currentConnection() {
    if (hasPlug())
      return plugged;
    else {
      std::cerr << "Cannot get connection of uplugged socket!\n";
      throw 1;
    }
  }
  double currentConstant() {
    if (hasPlug()) {
      std::cerr << "Cannot get constant of plugged socket!\n";
      throw 1;
    } else
      return constant;
  }
};
