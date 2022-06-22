#pragma once

#include "EvaluateUnits.h"
#include "NumberWithUnit.h"
#include "RegularExpressionSources.h"
#include "Units.h"
#include <iostream>
#include <regex>
#include <string_view>

using std::regex, std::regex_match, std::string;

/**
 * Base class for parsing c-style strings
 */
class Parse {
private:
  static const RegularExpressionSources regexs;

public:
  static float number(const string &str) {
    const regex re(regexs.number);
    bool isMatch = regex_match(str, re);
    if (isMatch)
      return stof(str);
    else
      throw 1;
  }

  static Units::Unit unit(const string &str) { return Units::parse(str); }

  static NumberWithUnit numberWithUnit(const string &str) {
    const regex re(regexs.numberWithUnit);
    std::smatch result;
    if (regex_match(str, result, re)) {
      const auto n = number(result[1]);
      const auto u = unit(result[2]);
      return {n, u};
    } else
      throw 1;
  }

  static float time(const string &str) {
    auto parsed = numberWithUnit(str);
    return EvaluateUnits::time(parsed.number, parsed.unit);
  }

  static float ratio(const string &str) {
    auto parsed = numberWithUnit(str);
    return EvaluateUnits::ratio(parsed.number, parsed.unit);
  }
};
