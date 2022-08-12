#include "../lib.h"

class RandomEnvelopeCommand : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

  BreakpointEnvelope env;

  float randf() { return float(rand() % 1000) / 1000; }

public:
  void run() override {

    srand(time(NULL));

    env.addSection(randf() * 100, randf() * 100, randf() * .8);
    do {
      if (randf() < .5)
        env.addSection(randf() * 100, randf() * .8);
      else
        env.addSection(randf() * 100, randf() * 100, randf() * .8);
    } while (randf() < .8);

    if (randf() < .5)
      env.closeTheLoop(randf() * .8);

    for (auto section : env.sections) {
      section.duration /= (section.startValue + section.endValue) / 200;
    }

    std::cout << env << "\n";
  }
};
