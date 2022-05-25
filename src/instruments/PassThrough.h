#pragma once

#include "../core.h"

template <typename T> class PassThrough : public NaiveInstrument<T> {
  Socket<T> &input = addSocket<T>();

  T tick() { return input(); }
};
