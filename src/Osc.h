#include "Constant.h"
#include "NaiveInstrument.h"

class Sawtooth : public NaiveInstrument<double> {
  double phase;
  NaiveInstrument *frequency;

public:
  Sawtooth(double f = 440) {
    phase = 0;
    frequency = new Constant(f);
  }

  double f() { return frequency->tickUntil(internalClock); }

public:
  double tick() {
    phase += f() / sampleRate;
    while (phase > 1)
      phase -= 1;
    return phase * 2 - 1;
  }
};
