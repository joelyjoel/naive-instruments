#pragma once
#include "Errors.h"

typedef enum { FAILED, PASSED } MaybeState;

/**
 * A container class for things that may or may not be available.
 */
template <typename T> class Hopefully {
  const T actual;
  const MaybeState state;

public:
  Hopefully(T actual) : actual(actual), state(PASSED) {}
  Hopefully(void) : state(FAILED){};

  bool success() const { return state; }
  const T access() const {
    if (success())
      return actual;
    else
      throw UnfulfilledMaybe;
  }

  const T operator*() const { return access(); }
};
