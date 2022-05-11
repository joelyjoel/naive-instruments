#pragma once
#include "NaiveInstrument.h"
#include "Patch.h"
#include "Socket.h"
#include "UnsignedSaw.h"
#include "Waveforms.h"
#include "Wavetable.h"
#include <iostream>

class Osc : public Patch<double> {
  UnsignedSaw phase;
  Wavetable wavetable;

public:
  Socket<double> &frequency = exposeSocket(phase.frequency);

public:
  Osc(double f = 440, MonoBuffer &waveform = Waveforms::sine())
      : Patch(wavetable) {
    frequency = f;
    wavetable.phase = phase;
    wavetable.setWaveform(waveform);

    std::cout << "created osc\n";
  }
};
