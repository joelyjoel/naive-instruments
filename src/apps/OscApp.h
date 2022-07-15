#include "../instruments/ControlString.h"
#include "../lib.h"
#include <iostream>

class OscApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    Sine osc;
    Pitch pitchConverter;

    const std::string str = args[0];
    auto &f = ControlString::parse(str);
    f.loop();

    std::cerr << "Frequency: " << f << "\n";

    osc.frequency << pitchConverter << f;

    output(osc);
  }
};
