#pragma once

#include "../core.h"
#include "NumberWithUnit.h"
#include "RegularExpressionSources.h"
#include <iostream>
#include <regex>
#include <string_view>

using std::regex, std::regex_match;

/**
 * Base class for parsing c-style strings
 */
class Parse {
private:
  static const RegularExpressionSources regexs;

public:
  static float number(const std::string &str) {
    const regex re(regexs.number);
    bool isMatch = regex_match(str, re);
    if (isMatch)
      return stof(str);
    else
      throw 1;
  }

  static NumberWithUnit numberWithUnit(const std::string &str) {
    const regex pattern(regexs.numberWithUnit);
    std::smatch result;
    bool isMatch = regex_match(str, result, pattern);
    float n = number(result[1].str());
    string unit = result[2].str();

    return {n, unit};
  }

  Unit unit(const std::string &str) {}

  static float time(const std::string &str) {
    auto parse = numberWithUnit(str);
  }
};
