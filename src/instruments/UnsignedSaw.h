#pragma once

#include "../core.h"
#include <string>

class UnsignedSaw : public Signal<double> {
public:
  SignalInput<double> &frequency = addInput<double>();
  double phase;

  void action() {
    phase += frequency() / sampleRate;
    while (phase > 1)
      phase -= 1.0;
    while (phase < 0)
      phase += 1.0;
    out(phase);
  }

  std::string label() { return "UnsignedSaw"; }
};
