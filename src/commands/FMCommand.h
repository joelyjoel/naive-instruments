#include "../lib.h"

class FMCommand : public CommandLineApp {

  using CommandLineApp::CommandLineApp;

public:
  void run() {
    int numberOfOscs = args.numberOfPositionalArgs();

    // Create the oscs
    std::vector<shared_ptr<Osc>> oscs;
    std::vector<shared_ptr<Signal<double>>> outputs;
    for (int i = 0; i < numberOfOscs; ++i) {
      shared_ptr<Osc> osc = make_shared<Sine>();
      oscs.push_back(osc);
      const std::string key = std::to_string(i);
      if (args.exists(key)) {
        shared_ptr<Signal<double>> level = args.signal(key);
        shared_ptr<Multiply> m = make_shared<Multiply>();
        m->a << osc;
        m->b << level;
        outputs.push_back(m);
      } else {
        outputs.push_back(osc);
      }
    }

    // Assign the fundamental frequencies
    shared_ptr<Signal<double>> fundamentalPitch = SignalString::parse(args[0]);
    shared_ptr<PitchConverter> fundamentalFrequency =
        make_shared<PitchConverter>();
    fundamentalFrequency->pitch << fundamentalPitch;
    for (int i = 0; i < numberOfOscs; ++i) {
      shared_ptr<Osc> osc = oscs[i];

      if (i == 0) {
        osc->frequency << fundamentalFrequency;
      } else {
        shared_ptr<Signal<double>> ratio = SignalString::parse(args[i]);
        shared_ptr<Multiply> m = make_shared<Multiply>();
        m->a << fundamentalFrequency;
        m->b << ratio;
        osc->frequency << m;
      }
    }

    // TODO: Add modulation routings
    for (int carrierIndex = 0; carrierIndex < numberOfOscs; ++carrierIndex) {
      for (int modulatorIndex = 0; modulatorIndex < numberOfOscs;
           ++modulatorIndex) {
        const std::string key = std::to_string(modulatorIndex) + "to" +
                                std::to_string(carrierIndex);
        if (args.exists(key)) {
          shared_ptr<Signal<double>> modulation = args.signal(key);

          shared_ptr<Multiply> m = make_shared<Multiply>();
          m->a << outputs[modulatorIndex];
          m->b << modulation;

          shared_ptr<IntervalToRatio> ratio = make_shared<IntervalToRatio>();
          ratio->interval << m;
          oscs[carrierIndex]->frequency *= ratio;
        }
      }
    }

    // Create the final mix
    shared_ptr<Signal<double>> mixdown;
    for (int i = 0; i < numberOfOscs; ++i) {
      shared_ptr<Signal<double>> oscOutput = outputs[i];
      const std::string key = std::to_string(i) + "-out";
      if (args.exists(key) || i == 0) {
        shared_ptr<Signal<double>> level = args.signal(key, i == 0 ? "1" : "0");

        if (mixdown)
          mixdown = oscOutput * level;
        else
          mixdown = mixdown + (oscOutput * level);
      }
    }

    if (mixdown != nullptr)
      output(*mixdown);
    else
      std::cerr << "Mixdown is null\n";
  }
};
