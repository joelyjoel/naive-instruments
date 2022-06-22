#include "Units.h"

class NumberWithUnit {
public:
  float number;
  Units::Unit unit;

  NumberWithUnit(float n, Units::Unit unit) : number(n), unit(unit) {}
};
