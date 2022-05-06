#include "NaiveInstrument.h"
#include "Socket.h"
#include "UnsignedSaw.h"
#include "Waveforms.h"
#include "Wavetable.h"

class Osc : public NaiveInstrument<double> {
  UnsignedSaw phase;
  Wavetable wavetable;

public:
  Osc(double f = 440, MonoBuffer &waveform = Waveforms::square()) {
    phase.frequency = f;
    wavetable.phase = &phase;
  }
};

class Sawtooth : public NaiveInstrument<double> {
  double phase;
  Socket<double> &frequency = addSocket<double>();

public:
  Sawtooth(double f = 440) {
    phase = 0;
    frequency = f;
  }

public:
  double tick() {
    phase += frequency() / sampleRate;
    while (phase > 1)
      phase -= 1;
    return phase * 2 - 1;
  }
};
