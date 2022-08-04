#include "../lib.h"

class MixApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() override {
    if (args.numberOfPositionalArgs() == 0) {
      error("Expected at least one sample.");
      return;
    }

    std::vector<Signal<double> *> samplers;

    for (int i = 0; i < args.numberOfPositionalArgs(); ++i) {
      // TODO: Use getSample instead
      samplers.push_back(new Sampler(args[i]));
    }

    auto *sum = Add::many(samplers);

    output(*sum);
  }
};
