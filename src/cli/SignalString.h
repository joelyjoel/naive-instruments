#pragma once

#include "../core.h"
#include "../instruments/Constant.h"
#include "../instruments/ControlSignal.h"
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

    Hopefully<ControlSignal *> controlSignal = ControlSignal::parse(str);
    if (controlSignal.success()) {
      std::cerr << "Using ControlSignal\n";
      return *controlSignal;
    }

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
