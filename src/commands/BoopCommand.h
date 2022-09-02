#include "../lib.h"

class BoopCommand : public AudioCommand {
  using AudioCommand::AudioCommand;

  void describeOptions() override {
    addWaveformOptions();
    addPitchOptions();
    describeOutputOptions();
  }

  void action() override {
    MonoBuffer &waveform = *inputWaveform();
    shared_ptr<Osc> osc = make_shared<Osc>(waveform);
    shared_ptr<PitchConverter> pitchConverter = make_shared<PitchConverter>();

    shared_ptr<Signal<double>> frequency = inputFrequency();
    shared_ptr<Decay> envelope = make_shared<Decay>();

    envelope->duration << inputDuration();

    osc->frequency << frequency;

    output(*(osc * envelope));
  }
};
