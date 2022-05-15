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

    modulator.frequency << 3;
    modulator.depth << .2;
    modulator.center << .5;
    waverer.a << carrier << 200;
    waverer.b << modulator;

    AudioSnapshotTest test4("a wavering sine wave", waverer, 5);
  }

  {
    Pitch pitchToFrequency;
    Sine osc;

    osc << pitchToFrequency << 60;

    AudioSnapshotTest("middle c", osc);
  }

  {
    LFO lfo;
    Pitch f;
    Sine carrier;

    lfo.frequency << 1;
    lfo.depth << 12;
    lfo.center << 60;

    carrier << f << lfo;

    AudioSnapshotTest("octave vibrato", carrier, 5);
  }

  {
    LFO lfo;
    Triangle carrier;
    Pitch pitchToFrequency;
    Floor floor;

    lfo.frequency << .1;
    lfo.depth << 12;
    lfo.center << 60;

    carrier << pitchToFrequency << floor << lfo;

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

  {
    Sine sine;
    Multiply attenuator;
    AHD ahd;

    ahd.attack << .4;
    ahd.hold << .5;
    ahd.decay << 2;
    attenuator.a << ahd;
    attenuator.b << sine << 60;

    AudioSnapshotTest("AHD attenuated sine", attenuator, 3);
  }

  {
    Triangle osc;
    Pitch pitchConverter;
    BreakpointEnvelope pitchEnvelope, amplitudeEnvelope;
    Multiply attenuator;

    amplitudeEnvelope.addSection(1, 1, .5);
    amplitudeEnvelope.addSection(1, 0, .75);

    pitchEnvelope.addSection(70, 30, .1);
    pitchEnvelope.addSection(30, -10, .9);

    attenuator.a << osc << pitchConverter << pitchEnvelope;
    attenuator.b << amplitudeEnvelope;

    AudioSnapshotTest("Shit kick", attenuator, 2);
  }

  {
    Triangle osc;
    Pitch pitchConverter;
    BreakpointEnvelope pitchEnvelope, amplitudeEnvelope;
    Multiply attenuator;

    amplitudeEnvelope.addSection(1, 1, .5);
    amplitudeEnvelope.addSection(1, 0, .75);

    pitchEnvelope.addSection(70, 30, .1);
    pitchEnvelope.addSection(30, -10, .9);

    attenuator.a << osc << pitchConverter << pitchEnvelope;
    attenuator.b << amplitudeEnvelope;

    Sine sin;
    Multiply ring;
    ring.a << attenuator;
    ring.b << sin << 35;

    AudioSnapshotTest("Bassey kick", ring, 2);
  }

  return 0;
}
