#include "../lib.h"
#include "./RandomEnvelopeApp.h"

class RandomApp : CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    const std::string &command = args[0];
    if (command == "envelope") {
      MainArgs subArgs = args.subCommandArguments();
      RandomEnvelopeApp app(subArgs);
      app.run();
    } else {
      std::cerr << "Unexpected sub-command: " << command << "\n";
    }
  }
};
