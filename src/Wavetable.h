#pragma once

#include "MonoBuffer.h"
#include "NaiveInstrument.h"
#include "Socket.h"
#include "Waveforms.h"
#include <string>

class Wavetable : public NaiveInstrument<double> {
  int bufferLength;

  MonoBuffer *waveform;

public:
  std::string label() { return "Wavetable"; }

  Socket<double> &phase = addSocket<double>();

  Wavetable(MonoBuffer &waveform = Waveforms::sine()) : waveform(&waveform) {}

  double tick() {
    return waveform->atIndex(phase() * waveform->numberOfSamples);
  }

  void setWaveform(MonoBuffer *buffer) { waveform = buffer; }
  void setWaveform(MonoBuffer &buffer) { waveform = &buffer; }
};
