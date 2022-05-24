#pragma once

#include "../core.h"

class ZeroCrossingDetector : public NaiveInstrument<bool> {
private:
  double previous = 0;
  double threshold = 0;

public:
  Socket<double> &input = addSocket<double>();
  bool detectDownwardsZeroCrossings = true;
  bool detectUpwardsZeroCrossings = false;

  bool tick() {
    double next = input();
    bool result = (detectDownwardsZeroCrossings && previous > threshold &&
                   next < -threshold) ||
                  (detectUpwardsZeroCrossings && previous < -threshold &&
                   next > threshold);

    if (next != 0)
      previous = next;

    return result;
  }

  void reset() { previous = 0; }
};
