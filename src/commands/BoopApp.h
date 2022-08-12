#include "../lib.h"

class BoopApp : public AudioCommand {
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
    Multiply m;

    Signal<double> *frequency = inputFrequency();
    Decay envelope;

    envelope.duration << inputDuration();

    osc << *frequency;
    m.a << osc;
    m.b << envelope;

    output(m);
  }
};
