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
  static Signal<double> *parse(const std::string str) {

    std::regex wavFileRegex(".wav$");
    if (std::regex_search(str, wavFileRegex)) {
      std::cerr << "SAMPLE: " << str << "\n";
      return new Sampler(str);
    }

    Hopefully<ControlString *> cs = ControlString::parse(str);
    if (cs.success())
      return *cs;

    try {
      double f = std::stoi(str);
      std::cerr << "Got osc " << f << " from " << str << "\n";
      return new Constant(f);
    } catch (std::invalid_argument err) {
      std::cerr << "Can't parse '" << str << "'\n";
      return new Constant(0);
    }
  }
};

void operator<<(SignalInput<double> &input, const std::string &str);
