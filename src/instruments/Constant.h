#pragma once

#include "../core.h"
#include <iostream>

class Constant : public NaiveInstrument<double> {
private:
  double value = 0;

public:
  Constant(double k) : value(k) {}
  double tick() { return value; }
};
