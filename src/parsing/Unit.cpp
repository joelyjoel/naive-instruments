#include "Unit.h"
#include <string>

Unit parseUnit(std::string &str) {
  if (str == "ms" || str == "milliseconds")
    return ms;
  if (str == "%")
    return percentage;
  if (str == "Hz")
    return Hz;
  else
    return noUnit;
}
