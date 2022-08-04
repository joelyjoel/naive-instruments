#include "../lib.h"

class MixApp : public AudioCommand {
  using AudioCommand::AudioCommand;

protected:
  void describeOptions() override {

    options.add_options()("input", po::value<std::vector<std::string>>(),
                          "Add a file to the mix");
    positionalOptions.add("input", -1);
  }

public:
  void action() override {
    if (args.count("input") == 0) {
      cerr << "Please define at least one input.\n";
      // TODO: return exit code, once that is supported
      return;
    }

    std::vector<Signal<double> *> samplers;

    auto inputFiles = args["input"].as<std::vector<std::string>>();
    for (int i = 0; i < inputFiles.size(); ++i) {
      // TODO: Use getSample instead
      samplers.push_back(new Sampler(inputFiles[i]));
    }

    auto *sum = Add::many(samplers);

    output(*sum);
  }
};
