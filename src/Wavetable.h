#pragma once

#include "MonoBuffer.h"
#include "NaiveInstrument.h"
#include "Socket.h"
#include "Waveforms.h"

class Wavetable : public NaiveInstrument<double> {
  int bufferLength;

  MonoBuffer *waveform;

public:
  Socket<double> &phase = addSocket<double>();

  Wavetable(MonoBuffer &waveform = Waveforms::sine()) : waveform(&waveform) {}

  double tick() {
    return waveform->atIndex(phase() * waveform->numberOfSamples);
  }

  void setWaveform(MonoBuffer *buffer) { waveform = buffer; }
  void setWaveform(MonoBuffer &buffer) { waveform = &buffer; }
};
