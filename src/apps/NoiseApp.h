#include "../lib.h"

class NoiseApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    Noise noise;
    output(noise);
  }
};
