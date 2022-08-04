#pragma once

#include "../core.h"

class Ramp : public Signal<double> {
private:
  double phase = 0;

public:
  SignalInput<double> &start = addSocket<double>(1.0);
  SignalInput<double> &end = addSocket<double>(0);
  SignalInput<double> &duration = addSocket<double>(1.0);

  double tick() {
    if (phase < 1) {
      phase += (1.0 / 44100.0) / duration();
      return phase * end() + (1 - phase) * start();
    } else
      return end();
  }
};
