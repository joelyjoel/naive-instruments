#pragma once

#include "../core.h"
#include <cmath>

class Floor : public Signal<double> {
public:
  SignalInput<double> &input = addSocket<double>();

  double tick() { return floor(input()); }
};
