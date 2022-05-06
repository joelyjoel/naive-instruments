#pragma once

#include "Constant.h"
#include "NaiveInstrument.h"

/**
 * Abstraction for the inputs to a NaiveInstrument
 */
template <typename SignalFrame> class Socket {
  UntypedInstrument *owner;

  NaiveInstrument<SignalFrame> *plugged;

public:
  Socket(UntypedInstrument *owner) : owner(owner) {}

  /**
   * Synchronise the plugged instrument with the owner
   */
  SignalFrame sync() { return plugged->tickUntil(owner->internalClock); }

  SignalFrame operator()() { return sync(); }

  void connect(NaiveInstrument<SignalFrame> *instrument) {
    plugged = instrument;
  }

  void setConstant(double k) { connect(new Constant(k)); }

  void operator=(NaiveInstrument<SignalFrame> *instrument) {
    connect(instrument);
  }

  void operator=(double k) { setConstant(k); }
};
