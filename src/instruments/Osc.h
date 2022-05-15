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
  Osc(MonoBuffer &waveform) : Patch(wavetable) {
    wavetable.phase << phase;
    wavetable.setWaveform(waveform);
  }

  std::string label() { return "Osc"; }
};

class Square : public Osc {
public:
  Square() : Osc(Waveforms::square()) {}
};

class Saw : public Osc {
public:
  Saw() : Osc(Waveforms::saw()) {}
};

class Sine : public Osc {
public:
  Sine() : Osc(Waveforms::sine()) {}
};

class Triangle : public Osc {
public:
  Triangle() : Osc(Waveforms::triangle()) {}
};
