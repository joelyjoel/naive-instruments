#pragma once
#include "NaiveInstrument.h"
#include "Socket.h"
#include "UnsignedSaw.h"
#include "Waveforms.h"
#include "Wavetable.h"
#include <iostream>

class Osc : public NaiveInstrument<double> {
  UnsignedSaw phase;
  Wavetable wavetable;

public:
  Socket<double> &frequency = phase.frequency;

public:
  Osc(double f = 440, MonoBuffer &waveform = Waveforms::sine()) {
    frequency = f;
    wavetable.phase = phase;
    wavetable.setWaveform(waveform);

    std::cout << "created osc\n";
  }

  double tick() { return ++wavetable; }
};
