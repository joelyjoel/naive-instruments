#include "../instruments/ControlString.h"
#include "../lib.h"
#include <iostream>

class OscCommand : public AudioCommand {
  using AudioCommand::AudioCommand;

  void describeOptions() override {
    describeOutputOptions();
    addPitchOptions();
    addWaveformOptions();
    addVibratoOptions();
    options.add_options()("volume",
                          po::value<std::string>()->default_value("1"),
                          "Output level of the oscillator from 0-1");
  }

public:
  void action() override {

    MonoBuffer &waveform = *inputWaveform();
    Osc osc(waveform);
    PitchConverter pitchConverter;
    Multiply gain;
    Add pitchSum;

    LFO vibrato;

    /* const std::string str = args[0]; */
    /* auto &f = **ControlString::parse(str); */

    Signal<double> &pitch = *inputPitch();

    vibrato.depth << args["vibrato-amount"].as<std::string>();
    vibrato.frequency << args["vibrato-frequency"].as<std::string>();
    pitchSum.a << pitch;
    pitchSum.b << vibrato;
    gain.a << osc << pitchConverter << pitchSum;
    gain.b << args["volume"].as<std::string>();

    output(gain);
  }
};
