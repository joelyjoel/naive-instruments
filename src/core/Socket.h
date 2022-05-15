#pragma once

#include "NaiveInstrument.h"

class AbstractSocket {
protected:
  UntypedInstrument *owner;

public:
  AbstractSocket(UntypedInstrument *owner) : owner(owner){};
};

/**
 * Abstraction for the inputs to a NaiveInstrument
 */
template <typename SignalFrame> class Socket : public AbstractSocket {

  NaiveInstrument<SignalFrame> *plugged;
  SignalFrame constant;

public:
  Socket(UntypedInstrument *owner)
      : AbstractSocket(owner), constant(0), plugged(nullptr) {}

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

  void operator<<(NaiveInstrument<SignalFrame> *instrument) {
    connect(instrument);
  }

  void operator<<(NaiveInstrument<SignalFrame> &instrument) {
    connect(&instrument);
  }

  void operator<<(double k) { setConstant(k); }
};
