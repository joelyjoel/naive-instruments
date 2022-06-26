#pragma once
#include "Errors.h"

typedef enum { Disappointment, Satisfaction } HopefullyState;

/**
 * A container class for things that may or may not be available.
 */
template <typename T> class Hopefully {

  // I know this must be wasting time copying objects multiple times, I
  // need to better understand C++ constructors/conversions to fix that

  T actual;
  const HopefullyState state;

public:
  Hopefully(T actual) : actual(actual), state(Satisfaction) {}
  Hopefully(HopefullyState state) : state(state) {}
  Hopefully(void) : state(Disappointment){};

  bool success() const { return state; }
  const T access() const {
    if (success())
      return actual;
    else
      throw UnfulfilledMaybe;
  }

  const T operator*() const { return access(); }
  const T *operator->() const { return &actual; }

  bool operator==(const T &operand) const {
    if (success())
      return operand == actual;
    else
      return false;
  }
};
