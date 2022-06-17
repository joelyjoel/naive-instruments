#include "../lib.h"
#include <iostream>

class OscApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    Saw osc;

    osc.frequency << args.signal(0);

    output(osc);
  }
};
