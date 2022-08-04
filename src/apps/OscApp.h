#include "../instruments/ControlString.h"
#include "../lib.h"
#include <iostream>

class OscApp : public AudioCommand {
  using AudioCommand::AudioCommand;

  void describeOptions() override {
    describeOutputOptions();
    options.add_options()

        ("pitch", po::value<std::string>()->default_value("50"),
         "Frequency of the oscillator expressed as a midi pitch number.")

            ("waveform", po::value<std::string>()->default_value("sine"),
             "Set the oscillator's waveform (sine|saw|square|triangle)")

                ("volume", po::value<std::string>()->default_value("1"),
                 "Output level of the oscillator from 0-1")

                    ("vibrato-frequency,vf",
                     po::value<std::string>()->default_value("5Hz"),
                     "Vibrato frequency")

                        ("vibrato-amount,va",
                         po::value<std::string>()->default_value("0"),
                         "Amount of vibrato (in semitones)");
  }

public:
  void action() override {

    MonoBuffer &waveform =
        Waveforms::byName(args["waveform"].as<std::string>());
    Osc osc(waveform);
    PitchConverter pitchConverter;
    Multiply gain;
    Add pitchSum;

    LFO vibrato;

    /* const std::string str = args[0]; */
    /* auto &f = **ControlString::parse(str); */

    Signal<double> &pitch =
        *SignalString::parse(args["pitch"].as<std::string>());
    Signal<double> &volume =
        *SignalString::parse(args["volume"].as<std::string>());
    Signal<double> &vibratoRate =
        *SignalString::parse(args["vibrato-frequency"].as<std::string>());
    Signal<double> &vibratoAmount =
        *SignalString::parse(args["vibrato-amount"].as<std::string>());

    vibrato.depth << vibratoAmount;
    vibrato.frequency << vibratoRate;
    pitchSum.a << pitch;
    pitchSum.b << vibrato;
    gain.a << osc << pitchConverter << pitchSum;
    gain.b << volume;

    output(gain);
  }
};
