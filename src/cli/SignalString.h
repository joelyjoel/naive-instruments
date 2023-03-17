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
  static shared_ptr<FrameStream<double>> parse(const std::string str) {

    std::regex wavFileRegex(".wav$");
    if (std::regex_search(str, wavFileRegex)) {
      std::cerr << "SAMPLE: " << str << "\n";
      return make_shared<Sampler>(str);
    }

    // TODO: use empty shared_ptr for failure?
    Hopefully<shared_ptr<ControlString>> cs = ControlString::parse(str);
    if (cs.success())
      return *cs;

    try {
      double f = std::stoi(str);
      std::cerr << "Got osc " << f << " from " << str << "\n";
      return make_shared<Constant>(f);
    } catch (std::invalid_argument err) {
      std::cerr << "Can't parse '" << str << "'\n";
      return make_shared<Constant>(0);
    }
  }
};

void operator<<(SignalInput<double> &input, const std::string &str);
