#include "../generative/Random.h"
#include "../lib.h"
#include "./RandomEnvelopeApp.h"

class RandomApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

  float randomFloat() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }

  float randomFloat(float max) { return randomFloat() * max; }
  float randomFloat(float min, float max) {
    return randomFloat() * (max - min) + min;
  }

public:
  void run() {

    if (!args.exists(0)) {
      std::cerr << "A random what?\n";
      return;
    }
    const std::string &command = args[0];

    if (command == "envelope") {
      MainArgs subArgs = args.subCommandArguments();
      RandomEnvelopeApp app(subArgs);
      app.run();
    } else if (command == "frequency")
      frequency();
    else if (command == "pitch")
      pitch();
    else
      std::cerr << "Unexpected sub-command: " << command << "\n";
  }

private:
  uint64_t seed() {
    if (args.exists("seed"))
      return args.number("seed");
    else
      return Random::clockSeed();
  }

  Random random = seed();

  void frequency() {
    double min = args.number("min", 20);
    double max = args.number("max", 20000);
    std::cout << random.number(min, max) << "Hz\n";
  }

  void pitch() {
    double min = args.number("min", 21);
    double max = args.number("max", 108);
    std::cout << random.number(min, max) << "MIDI\n";
  }
};
