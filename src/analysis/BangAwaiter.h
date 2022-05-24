#pragma once

#include "../core.h"

const int LIMIT_EXCEEDED = 99;

/**
 * Use this to wait for bangs (true values in a boolean signal);
 */
class BangAwaiter {
private:
  NaiveInstrument<bool> *signal;

public:
  void next(int limit = 44100) {
    while (++(*signal) == false)
      if (--limit > 0)
        continue;
      else
        throw LIMIT_EXCEEDED;
  }

  NaiveInstrument<bool> &operator<<(NaiveInstrument<bool> &input) {
    signal = &input;
    return input;
  }
};
