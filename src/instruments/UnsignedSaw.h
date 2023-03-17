#pragma once

#include "../core.h"
#include <string>

class UnsignedSaw : public FrameStream<double> {
public:
  SignalInput<double> frequency{this, "frequency/Hz"};
  double phase;

  void action() override {
    phase += frequency() / sampleRate;
    while (phase > 1)
      phase -= 1.0;
    while (phase < 0)
      phase += 1.0;
    out(phase);
  }

  void resetState() override { phase = 0; }

  std::string label() override { return "UnsignedSaw"; }
};
