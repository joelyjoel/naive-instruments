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
    Osc osc(waveform);
    PitchConverter pitchConverter;

    Signal<double> *frequency = inputFrequency();
    Decay envelope;

    envelope.duration << inputDuration();

    osc << *frequency;

    output(*((osc) * (envelope)));
  }
};
