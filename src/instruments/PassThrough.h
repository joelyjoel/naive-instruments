#pragma once

#include "../core.h"

template <typename T> class PassThrough : public Signal<T> {
  SignalInput<T> &input = addInput<T>();

  void action() { out(input()); }
};
