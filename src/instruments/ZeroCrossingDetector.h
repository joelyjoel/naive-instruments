#pragma once

#include "../core.h"

class ZeroCrossingDetector : public Signal<bool> {
private:
  double previous = 0;
  double threshold = 0;

public:
  SignalInput<double> input{this, "input/audio"};
  bool detectDownwardsZeroCrossings = true;
  bool detectUpwardsZeroCrossings = false;

  void action() {
    double next = input();
    bool result = (detectDownwardsZeroCrossings && previous > threshold &&
                   next < -threshold) ||
                  (detectUpwardsZeroCrossings && previous < -threshold &&
                   next > threshold);

    if (next != 0)
      previous = next;

    out(result);
  }

  void reset() { previous = 0; }
};
