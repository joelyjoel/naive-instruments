#pragma once

#include "../core.h"
#include <cmath>

class Floor : public Signal<double> {
public:
  Socket<double> &input = addSocket<double>();

  double tick() { return floor(input()); }
};
