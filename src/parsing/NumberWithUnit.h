#pragma once

#include "../core.h"
#include "NumberPatterns.h"
#include "Units.h"
#include <regex>

class NumberWithUnit {
public:
  float number;
  Units::Unit unit;

  NumberWithUnit(float n, Units::Unit unit) : number(n), unit(unit) {}
  NumberWithUnit() : number(0), unit(Units::noUnit) {}

  static LazyRegex pattern;

  static Hopefully<NumberWithUnit> parse(const std::string &str) {
    std::smatch result;
    if (std::regex_match(str, result, *pattern)) {
      Hopefully<float> n = NumberPatterns::parseNumber(result[1]);
      Hopefully<Units::Unit> u = Units::parse(result[2]);
      if (n.success() && u.success())
        return NumberWithUnit(*n, *u);
      else
        return Disappointment;
    } else
      return Disappointment;
  }
};
