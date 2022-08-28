#pragma once

#include "../core.h"

class Ramp : public Signal<double> {
private:
  double phase = 0;

public:
  SignalInput<double> &start = addInput<double>("start", 1.0);
  SignalInput<double> &end = addInput<double>("end", 0);
  SignalInput<double> &duration = addInput<double>("duration/s", 1.0);

  void action() {
    if (phase < 1) {
      phase += (1.0 / 44100.0) / duration();
      out(phase * end() + (1 - phase) * start());
    } else
      out(end());
  }
};
