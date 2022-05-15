#include "lib.h"
#include "test-framework.h"
#include <iostream>

int main() {

  {
    Sine osc;
    osc << 440;
    AudioSnapshotTest("a sine wave", osc);
  }
  {
    Triangle osc;
    osc.frequency << 100;
    AudioSnapshotTest("a triangle wave", osc);
  }
  {
    Square osc;
    osc << 100;
    AudioSnapshotTest("a square wave", osc);
  }
  {
    Saw saw;
    saw << 100;
    AudioSnapshotTest("a sawtooth wave", saw);
  }

  {
    Sine carrier;
    LFO modulator;
    Multiply waverer;

    carrier << 200;
    modulator.frequency << 3;
    modulator.depth << .2;
    modulator.center << .5;
    waverer.a << carrier;
    waverer.b << modulator;

    AudioSnapshotTest test4("a wavering sine wave", waverer, 5);
  }

  {
    Pitch pitchToFrequency;
    Sine osc;

    pitchToFrequency << 60;
    osc << pitchToFrequency;

    AudioSnapshotTest("middle c", osc);
  }

  {
    LFO lfo;
    Pitch f;
    Sine carrier;

    lfo.frequency << 1;
    lfo.depth << 12;
    lfo.center << 60;
    f << lfo;
    carrier << f;

    AudioSnapshotTest("octave vibrato", carrier, 5);
  }

  {
    LFO lfo;
    Triangle carrier;
    Pitch f;
    Floor steps;

    lfo.frequency << .1;
    lfo.depth << 12;
    lfo.center << 60;
    steps << lfo;
    f << steps;
    carrier << f;

    AudioSnapshotTest("octave discrete vibrato", carrier, 5);
  }

  {
    Ramp ramp;
    Triangle source;
    Multiply attenuator;

    source << 60;
    ramp.start << 1.0;
    ramp.end << 0.0;
    ramp.duration << .5;

    attenuator.a << source;
    attenuator.b << ramp;

    AudioSnapshotTest("boop", attenuator);
  }

  return 0;
}
