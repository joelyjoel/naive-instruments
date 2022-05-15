#pragma once

#include "../core.h"

class Constant : public NaiveInstrument<double> {

  double value;

public:
  Constant(double value) : value(value) {}

  double tick() { return value; }
};
