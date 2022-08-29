#pragma once

#include "../core.h"

template <typename T> class PassThrough : public Signal<T> {
  SignalInput<T> input{this, "input"};

  void action() { out(input()); }
};
