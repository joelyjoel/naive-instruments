#include "../lib.h"

class OscApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    Sine osc;

    osc.frequency << stof(args[0]);

    output(osc);
  }
};
