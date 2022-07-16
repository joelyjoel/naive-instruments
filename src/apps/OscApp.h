#include "../instruments/ControlString.h"
#include "../lib.h"
#include <iostream>

class OscApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {

    auto waveform = Waveforms::byName(args.string("waveform", "sine"));

    Osc osc(waveform);
    Pitch pitchConverter;
    Multiply gain;
    Add pitchSum;

    LFO vibrato;

    /* const std::string str = args[0]; */
    /* auto &f = **ControlString::parse(str); */

    NaiveInstrument<double> &pitch = *args.signal("pitch", "50");
    NaiveInstrument<double> &volume = *args.signal("volume", "1");
    NaiveInstrument<double> &vibratoRate = *args.signal("vf", "5");
    NaiveInstrument<double> &vibratoAmount = *args.signal("va", "0");

    vibrato.depth << vibratoAmount;
    vibrato.frequency << vibratoRate;
    pitchSum.a << pitch;
    pitchSum.b << vibrato;
    gain.a << osc << pitchConverter << pitchSum;
    gain.b << volume;

    output(gain);
  }
};
