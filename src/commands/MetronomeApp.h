#include "../lib.h"

class MetronomeApp : public AudioCommand {

  using AudioCommand::AudioCommand;

  void describeOptions() override {
    describeOutputOptions();
    options.add_options()("bpm,beats-per-minute",
                          po::value<string>()->default_value("139"),
                          "What beats per minute should the metronome play")(
        "pattern", po::value<string>()->default_value("10101010"),
        "Binary rhythmic pattern");
  }

  void action() override {
    Sine osc;
    osc.frequency << 600;
    auto envelope = *ControlString::parse("100ms:1~0");
    Multiply attenuator;
    attenuator.a << osc;
    attenuator.b << envelope;

    Rhythm &rhythm = *Rhythm::fromBinaryString(args["pattern"].as<string>());
    rhythm.bpm << SignalString::parse(args["bpm"].as<string>());

    Resetter resetter;
    resetter.input << attenuator;
    resetter.trigger << rhythm;

    output(resetter);
  }
};
