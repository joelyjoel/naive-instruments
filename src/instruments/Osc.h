#pragma once

#include "../Waveforms.h"
#include "../core.h"
#include "UnsignedSaw.h"
#include "Wavetable.h"
#include <iostream>
#include <string>

class Osc : public Patch<double> {
  UnsignedSaw phase;
  Wavetable wavetable;

public:
  Socket<double> &frequency = exposeSocket(phase.frequency);

public:
  Osc(double f, MonoBuffer &waveform = Waveforms::sine()) : Patch(wavetable) {
    frequency = f;
    wavetable.phase = phase;
    wavetable.setWaveform(waveform);
  }

  std::string label() { return "Osc"; }
};

class Square : public Osc {
public:
  Square(double f) : Osc(f, Waveforms::square()) {}
};

class Saw : public Osc {
public:
  Saw(double f) : Osc(f, Waveforms::saw()) {}
};
