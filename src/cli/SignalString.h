#pragma once

#include "../core.h"
#include "../instruments/Constant.h"
#include "../instruments/ControlString.h"
#include "../instruments/Sampler.h"

#include <iostream>
#include <regex>
#include <string>

class SignalString {
public:
  static NaiveInstrument<double> *parse(const std::string str) {

    std::regex wavFileRegex(".wav$");
    if (std::regex_search(str, wavFileRegex)) {
      std::cerr << "SAMPLE: " << str << "\n";
      return new Sampler(str);
    }

    if (NumberWithUnit::pattern.test(str)) {
      std::cerr << "'" << str << "' could be a constant\n";
      try {
        double f = std::stoi(str);
        std::cerr << "Got const " << f << " from " << str << "\n";
        return new Constant(f);
      } catch (std::invalid_argument err) {
        std::cerr << "Can't parse '" << str << "' as contant\n";
        throw 1;
      }
    }

    Hopefully<ControlString *> cs = ControlString::parse(str);
    if (cs.success())
      return *cs;

    std::cerr << "Can't parse '" << str << "'\n";
    throw 1;
  }
};
