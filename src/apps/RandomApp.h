#include "../generative/Random.h"
#include "../lib.h"
#include "./RandomEnvelopeApp.h"

class RandomApp : CommandLineApp {
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
    const std::string &command = args[0];
    if (command == "envelope") {
      MainArgs subArgs = args.subCommandArguments();
      RandomEnvelopeApp app(subArgs);
      app.run();
    } else if (command == "frequency")
      frequency();
    else if (command == "pitch") {
      pitch();
    } else {
      std::cerr << "Unexpected sub-command: " << command << "\n";
    }
  }

private:
  Random random;

  void frequency() {
    double min = args.number("min", 20);
    double max = args.number("max", 20000);
    std::cout << random.frequency(min, max) << "Hz\n";
  }

  void pitch() {
    double min = args.number("min", 21);
    double max = args.number("max", 108);
    std::cout << random.pitch(min, max) << "MIDI\n";
  }
};
