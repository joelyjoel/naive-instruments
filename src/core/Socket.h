#pragma once

#include "NaiveInstrument.h"

/**
 * Abstraction for the inputs to a NaiveInstrument
 */
template <typename SignalFrame> class Socket {
  UntypedInstrument *owner;

  NaiveInstrument<SignalFrame> *plugged;
  SignalFrame constant;

public:
  Socket(UntypedInstrument *owner)
      : owner(owner), constant(0), plugged(nullptr) {}

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

  void connect(NaiveInstrument<SignalFrame> *instrument) {
    plugged = instrument;
  }

  void disconnect() { plugged = nullptr; }

  void setConstant(double k) {
    disconnect();
    constant = k;
  }

  void operator=(NaiveInstrument<SignalFrame> *instrument) {
    connect(instrument);
  }

  void operator=(NaiveInstrument<SignalFrame> &instrument) {
    connect(&instrument);
  }

  void operator=(double k) { setConstant(k); }
};
