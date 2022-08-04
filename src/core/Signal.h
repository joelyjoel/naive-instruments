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
