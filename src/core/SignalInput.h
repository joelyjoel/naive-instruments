#pragma once

#include "Signal.h"
#include "UntypedSignalInput.h"
#include <iostream>

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
  SignalFrame sync() {
    if (connection)
      return connection->tickUntil(owner->internalClock);
    else
      return constant;
  }

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
