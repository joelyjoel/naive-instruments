#pragma once

#include "NaiveInstrument.h"
#include <iostream>

class AbstractSocket {
protected:
  UntypedInstrument *owner;

public:
  AbstractSocket(UntypedInstrument *owner) : owner(owner){};

  virtual void connect(NaiveInstrument<double> *signal) {
    std::cerr << "No override for "
                 "AbstractSocket::connect(NaiveInstrument<double>*) method\n";
    throw YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE;
  }

  virtual void setConstant(double k) {
    std::cerr << "No override for AbstractSocket::setConstant(double) method\n";
    throw YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE;
  }
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
