#pragma once

#include "UntypedSignal.h"
#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

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
      tick();
    }
    return latestFrame;
  }

  /**
   * Naive instruments work a bit like clock work. Every frame of the digital
   * signal they "tick". What they actually do when they tick is up to them!
   */
  virtual void tick() {
    std::cerr
        << "Oh no, looks like the programmer forgot to implement the tick "
           "method for a Signal\n";
    throw 1;
  }

public:
  virtual void reset() {
    std::cerr << "The reset method has not been implemented for this unit\n";
    throw 1;
  }

  SignalFrame operator[](int index) { return tickUntil(index); }

  SignalFrame next() { return tickUntil(internalClock + 1); }
  SignalFrame operator++() { return next(); }

  UntypedSignalInput &defaultSocket() {
    if (sockets.size() > 0)
      return *sockets[0];
    else {
      std::cerr << "There is no socket!\n";
      throw 1;
    }
  }

  template <typename InputSignalFrame>
  Signal<InputSignalFrame> &operator<<(Signal<InputSignalFrame> &signal) {
    defaultSocket().connect(&signal);
    return signal;
  }

  void operator<<(double k) { defaultSocket().setConstant(k); }
};
