#pragma once

#include "../core.h"

template <typename T> class PassThrough : public Signal<T> {
  SignalInput<T> &input = addSocket<T>();

  void tick() { out(input()); }
};
