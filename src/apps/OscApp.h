#include "../instruments/ControlString.h"
#include "../lib.h"
#include <iostream>

class OscApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    Sine osc;
    Pitch pitchConverter;
    Multiply gain;

    LFO vibrato;

    /* const std::string str = args[0]; */
    /* auto &f = **ControlString::parse(str); */

    NaiveInstrument<double> &pitch = *args.signal("pitch", "50");

    NaiveInstrument<double> &volume = *args.signal("volume", "1");

    gain.a << osc << pitchConverter << pitch;
    gain.b << volume;

    output(gain);
  }
};
