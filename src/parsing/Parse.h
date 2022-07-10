#pragma once

#include "../core.h"
#include "EvaluateUnits.h"
#include "NumberWithUnit.h"
#include "RegularExpressionSources.h"
#include "Units.h"
#include <iostream>
#include <regex>
#include <string_view>

using std::regex, std::string;

/**
 * Base class for parsing c-style strings
 */
class Parse {
private:
  static const RegularExpressionSources regexs;

public:
  static Hopefully<float> number(const string &str) {
    return NumberPatterns::parseNumber(str);
  }

  static Hopefully<Units::Unit> unit(const string &str) {
    return Units::parse(str);
  }

  static Hopefully<NumberWithUnit> numberWithUnit(const string &str) {
    return NumberWithUnit::parse(str);
  }

  static Hopefully<float> time(const string &str) {
    Hopefully<NumberWithUnit> parsed = numberWithUnit(str);
    if (parsed.success()) {
      return EvaluateUnits::time(*parsed);
    } else
      return Disappointment;
  }

  /**
   * Parse time using a sample as context.
   */
  static Hopefully<float> time(const string &str, MonoBuffer sample) {
    auto parsed = numberWithUnit(str);
    if (parsed.success())
      return EvaluateUnits::time(*parsed, sample);
    return Disappointment;
  }

  static Hopefully<float> ratio(const string &str) {
    auto parsed = numberWithUnit(str);
    // TODO: Parse ratios like 2:3
    // TODO: Parse fractions like 1/2
    if (parsed.success())
      return EvaluateUnits::ratio(*parsed);
    else
      return Disappointment;
  }

  static Hopefully<float> frequency(const string &str) {
    // TODO: Parse midi note names
    auto parsed = numberWithUnit(str);
    if (parsed.success())
      return EvaluateUnits::frequency(*parsed);
    else
      return Disappointment;
  }

  static Hopefully<float> bpm(const string &str) {
    auto parsed = numberWithUnit(str);
    if (parsed.success())
      return EvaluateUnits::bpm(*parsed);
    else
      return Disappointment;
  }

  static Hopefully<float> interval(const string &str) {
    auto parsed = numberWithUnit(str);
    if (parsed.success())
      return EvaluateUnits::interval(*parsed);
    else
      return Disappointment;
  }
};
