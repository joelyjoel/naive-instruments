#pragma once

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
    std::cerr << "\n" << regexs.number << "\n\n";
    const regex re(regexs.number);
    bool isMatch = regex_match(str, re);
    if (isMatch)
      return stof(str);
    else
      throw 1;
  }
};
