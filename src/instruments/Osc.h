#pragma once

#include "../Waveforms.h"
#include "../core.h"
#include "UnsignedSaw.h"
#include "Wavetable.h"
#include <iostream>
#include <string>

// TODO: Probably could be converted into a function or something once shared
// pointers are fully adopted
class Osc : public Patch<double> {
  shared_ptr<UnsignedSaw> phase{make_shared<UnsignedSaw>()};
  shared_ptr<Wavetable> wavetable{make_shared<Wavetable>()};

public:
  SignalInput<double> &frequency = exposeInput(phase->frequency);

public:
  Osc(MonoBuffer &waveform) {
    wavetable->phase << phase;
    wavetable->setWaveform(waveform);
    exposeOutput(wavetable);
  }

  std::string label() override { return "Osc"; }
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
