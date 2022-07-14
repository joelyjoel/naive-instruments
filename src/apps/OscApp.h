#include "../instruments/ControlString.h"
#include "../lib.h"
#include <iostream>

class OscApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    Sine osc;

    const std::string str = args[0];
    auto &f = ControlString::parse(str);

    osc.frequency << f;

    output(osc);
  }
};
