#include "Unit.h"
#include <string>

using std::string;

class NumberWithUnit {
public:
  const float number;
  Unit unit;

  NumberWithUnit(float n, Unit unit) : unit(unit), number(n) {}
  NumberWithUnit(float n, string unit) : NumberWithUnit(n, parseUnit(unit)) {}
};
