#pragma once

#include "NaiveInstrument.h"
#include "Socket.h"
#include "constants.h"
#include <string>

class UnsignedSaw : public NaiveInstrument<double> {
public:
  Socket<double> &frequency = addSocket<double>();
  double phase;

  double tick() {
    phase += frequency() / sampleRate;
    while (phase > 1)
      --phase;
    while (phase < 0)
      ++phase;
    return phase;
  }

  std::string label() { return "UnsignedSaw"; }
};
