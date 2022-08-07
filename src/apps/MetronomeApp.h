#include "../lib.h"

class MetronomeApp : public AudioCommand {

  using AudioCommand::AudioCommand;

  void describeOptions() override {
    options.add_options()("bpm,beats-per-minute",
                          po::value<std::string>()->default_value("139"),
                          "What beats per minute should the metronome play");
  }

  void action() override {
    Sine osc;
    osc.frequency << 600;
    auto envelope = *ControlString::parse("100ms:1~0");
    Multiply attenuator;
    attenuator.a << osc;
    attenuator.b << envelope;

    MetronomicResetter metro;
    metro.input << attenuator;
    metro.bpm << SignalString::parse(args["bpm"].as<std::string>());

    output(metro);
  }
};
