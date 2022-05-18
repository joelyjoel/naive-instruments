#pragma once

#include "../core.h"
#include <string>

class UnsignedSaw : public NaiveInstrument<double> {
public:
  Socket<double> &frequency = addSocket<double>();
  double phase;

  double tick() {
    phase += frequency() / sampleRate;
    while (phase > 1)
      phase -= 1.0;
    while (phase < 0)
      phase -= 1.0;
    return phase;
  }

  std::string label() { return "UnsignedSaw"; }
};
