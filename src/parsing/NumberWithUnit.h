#pragma once

#include "Units.h"

class NumberWithUnit {
public:
  float number;
  Units::Unit unit;

  NumberWithUnit(float n, Units::Unit unit) : number(n), unit(unit) {}
  NumberWithUnit() : number(0), unit(Units::noUnit) {}
};
