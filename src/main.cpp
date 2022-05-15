#include "lib.h"
#include "test-framework.h"

int main() {

  { AudioSnapshotTest("a sine wave", new Sine(440)); }
  { AudioSnapshotTest("a triangle wave", new Triangle(100)); }
  { AudioSnapshotTest("a square wave", new Square(100)); }
  { AudioSnapshotTest("a sawtooth wave", new Saw(100)); }

  {
    Sine carrier(200);
    LFO modulator(3, .2, .5);
    Multiply waverer;
    waverer.a = carrier;
    waverer.b = modulator;
    AudioSnapshotTest test4("a wavering sine wave", waverer, 5);
  }

  {
    Pitch frequency(60);
    Sine osc(frequency);
    AudioSnapshotTest("middle c", osc);
  }

  {
    LFO lfo(1, 12, 60);
    Pitch f(lfo);
    Sine carrier(f);
    AudioSnapshotTest("octave vibrato", carrier, 5);
  }

  {
    LFO lfo(.1, 12, 60);
    Floor steps(lfo);
    Pitch f(steps);
    Triangle carrier(f);
    AudioSnapshotTest("octave discrete vibrato", carrier, 5);
  }

  return 0;
}
