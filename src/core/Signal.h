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
  SignalFrame operator[](int index) { return tickUntil(index); }

  SignalFrame next() { return tickUntil(internalClock + 1); }
  SignalFrame operator++() { return next(); }

  UntypedSignalInput &defaultInput() {
    if (inputs.size() > 0)
      return *inputs[0];
    else {
      std::cerr << "Trying to get default input but the Signal has no inputs";
      throw 1;
    }
  }

  template <typename InputSignalFrame>
  Signal<InputSignalFrame> &operator<<(Signal<InputSignalFrame> &signal) {
    defaultInput().connect(&signal);
    return signal;
  }

  void operator<<(double k) { defaultInput().setConstant(k); }
};
