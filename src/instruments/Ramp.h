#pragma once

#include "../core.h"

class Ramp : public Signal<double> {
private:
  double phase = 0;

public:
  SignalInput<double> start{this, "start"};
  SignalInput<double> end{this, "end"};
  SignalInput<double> duration{this, "duration/s"};

  void action() {
    if (phase < 1) {
      phase += (1.0 / 44100.0) / duration();
      out(phase * end() + (1 - phase) * start());
    } else
      out(end());
  }
};
