#include "lib.h"
#include "test-framework.h"

int main() {

  AudioSnapshotTest test1("a sine wave", new Sine(440));
  AudioSnapshotTest test2("a square wave", new Square(100));
  AudioSnapshotTest test3("a sawtooth wave", new Saw(100));

  {
    Sine carrier(200);
    LFO modulator(3, .2, .5);
    Multiply waverer;
    waverer.a = carrier;
    waverer.b = modulator;
    AudioSnapshotTest test4("a wavering sine wave", waverer, 5);
  }

  return 0;
}
