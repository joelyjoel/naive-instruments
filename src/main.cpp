#include "TestUtils.h"
#include "lib.h"

int main() {

  AudioSnapshotTest test1("a sine wave", new Osc(440));
  AudioSnapshotTest test2("a square wave", new Square(100));
  AudioSnapshotTest test3("a sawtooth wave", new Saw(100));

  return 0;
}
