#include "../lib.h"

class FMApp : CommandLineApp {

  using CommandLineApp::CommandLineApp;

public:
  void run() {
    int numberOfOscs = args.numberOfPositionalArgs();

    // Create the oscs
    std::vector<Osc *> oscs;
    for (int i = 0; i < numberOfOscs; ++i)
      oscs.push_back(new Sine());

    // Assign the frequencies
    for (int i = 0; i < numberOfOscs; ++i) {
      Osc *osc = oscs[i];

      NaiveInstrument<double> *pitch = SignalString::parse(args[i]);
      Pitch *pitchConverter = new Pitch();
      osc->frequency << pitchConverter << *pitch;
    }

    NaiveInstrument<double> *mixdown = nullptr;
    for (int i = 0; i < numberOfOscs; ++i) {
      Osc *osc = oscs[i];
      if (mixdown == nullptr) {
        mixdown = osc;
      } else {
        Add *add = new Add();
        add->a << mixdown;
        add->b << osc;
        mixdown = add;
      }
    }

    if (mixdown != nullptr)
      output(*mixdown);
    else
      std::cerr << "Mixdown is null\n";
  }
};
