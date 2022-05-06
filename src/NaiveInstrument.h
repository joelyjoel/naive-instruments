#pragma once

#include "constants.h"

#define YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE 420
#define CANT_ACCESS_SIGNAL_FROM_THE_PAST_ERROR_CODE 69

/**
 * I think its intuitive to think of audio processes like little machines.
 */
template <typename SignalFrame> class NaiveInstrument {
protected:
  int internalClock;
  SignalFrame y;

public:
  SignalFrame tickUntil(int time) {
    while (internalClock < time) {
      ++internalClock;
      y = tick();
    }
    if (time > internalClock)
      throw CANT_ACCESS_SIGNAL_FROM_THE_PAST_ERROR_CODE;
    return y;
  }

  /**
   * Naive instruments work a bit like clock work. Every frame of the digital
   * signal they "tick". What they actually do when they tick is up to them!
   */
  virtual SignalFrame tick() {
    throw YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE;
  }

  double operator[](int index) { return tickUntil(index); }
};
