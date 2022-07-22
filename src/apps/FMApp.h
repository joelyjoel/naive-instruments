#include "../lib.h"

class FMApp : CommandLineApp {

  using CommandLineApp::CommandLineApp;

public:
  void run() {
    int numberOfOscs = args.numberOfPositionalArgs();

    // Create the oscs
    std::vector<Osc *> oscs;
    std::vector<NaiveInstrument<double> *> outputs;
    for (int i = 0; i < numberOfOscs; ++i) {
      Osc *osc = new Sine;
      oscs.push_back(osc);
      const std::string key = std::to_string(i);
      if (args.exists(key)) {
        NaiveInstrument<double> *level = args.signal(key);
        Multiply *m = new Multiply;
        m->a << osc;
        m->b << level;
        outputs.push_back(m);
      } else {
        outputs.push_back(osc);
      }
    }

    // Assign the fundamental frequencies
    std::vector<Socket<double> *> pitchSockets;
    for (int i = 0; i < numberOfOscs; ++i) {
      Osc *osc = oscs[i];

      NaiveInstrument<double> *pitch = SignalString::parse(args[i]);
      Pitch *pitchConverter = new Pitch();
      osc->frequency << pitchConverter << *pitch;

      pitchSockets.push_back(&pitchConverter->pitch);
    }

    // TODO: Add modulation routings
    for (int carrierIndex = 0; carrierIndex < numberOfOscs; ++carrierIndex) {
      for (int modulatorIndex = 0; modulatorIndex < numberOfOscs;
           ++modulatorIndex) {
        const std::string key = std::to_string(modulatorIndex) + "to" +
                                std::to_string(carrierIndex);
        if (args.exists(key)) {
          NaiveInstrument<double> *modulation = args.signal(key);
          Multiply *m = new Multiply();
          m->a << outputs[modulatorIndex];
          m->b << modulation;
          std::cout << "Modulating Osc" << carrierIndex << " by Osc"
                    << modulatorIndex << "\n";
          Socket<double> &socket = *pitchSockets[carrierIndex];

          if (socket.hasPlug()) {
            Add *adder = new Add();
            adder->a << m;
            adder->b << socket.currentConnection();
            socket << adder;
          } else {
            Add *adder = new Add();
            adder->a << m;
            adder->b << socket.currentConstant();
            socket << adder;
          }
        }
      }
    }

    // Create the final mix
    NaiveInstrument<double> *mixdown = nullptr;
    for (int i = 0; i < numberOfOscs; ++i) {
      NaiveInstrument<double> *oscOutput = outputs[i];
      const std::string key = std::to_string(i) + "-out";
      if (args.exists(key) || i == 0) {
        NaiveInstrument<double> *level = args.signal(key, i == 0 ? "1" : "0");
        Multiply *m = new Multiply;
        m->a << oscOutput;
        m->b << level;

        if (mixdown == nullptr) {
          mixdown = m;
        } else {
          Add *add = new Add();
          add->a << mixdown;
          add->b << m;
          mixdown = add;
        }
      }
    }

    if (mixdown != nullptr)
      output(*mixdown);
    else
      std::cerr << "Mixdown is null\n";
  }
};
