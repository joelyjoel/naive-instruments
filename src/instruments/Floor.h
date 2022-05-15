#pragma once

#include "../core.h"
#include <cmath>

class Floor : public NaiveInstrument<double> {
public:
  Socket<double> &input = addSocket<double>();

  Floor(NaiveInstrument<double> &signal) { input = signal; }

  double tick() { return floor(input()); }
};
