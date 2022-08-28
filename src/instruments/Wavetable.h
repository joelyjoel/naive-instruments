#pragma once

#include "../Waveforms.h"
#include "../core.h"
#include <string>

class Wavetable : public Signal<double> {
  int bufferLength;

  MonoBuffer *waveform;

public:
  std::string label() { return "Wavetable"; }

  SignalInput<double> &phase = addInput<double>("phase/0-1");

  Wavetable(MonoBuffer &waveform = Waveforms::sine()) : waveform(&waveform) {}

  void action() {
    out(waveform->interpolate(phase() * double(waveform->numberOfSamples)));
  }

  void setWaveform(MonoBuffer *buffer) { waveform = buffer; }
  void setWaveform(MonoBuffer &buffer) { waveform = &buffer; }
};
