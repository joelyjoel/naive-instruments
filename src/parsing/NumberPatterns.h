#include "../core.h"
#include "LazyRegex.h"

class NumberPatterns {
public:
  static LazyRegex naturalNumber;
  static LazyRegex integer;

  static LazyRegex unsignedDecimal;
  static LazyRegex unsignedPointNumber;

  static LazyRegex number;

  // TODO: Move these two to relevant classes
  static LazyRegex unit;
  static LazyRegex numberWithUnit;

public:
  static Hopefully<float> parseNumber(const std::string &str) {
    if (number.test(str))
      return stof(str);
    else
      return Disappointment;
  }
};
