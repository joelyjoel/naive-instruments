#pragma once

#include "../core.h"
#include <cmath>

class Floor : public Signal<double> {
public:
  SignalInput<double> &input = addSocket<double>();

  void tick() { out(floor(input())); }
};
