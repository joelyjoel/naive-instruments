#include "./makeASawToothWave.h"
#include "WavWriter.h"
#include <iostream>
#include <ostream>

int main() {
  // double *buffer = record1SecondSawtoothWave();

  Sawtooth osc(200);
  const int numberOfFrames = sampleRate * 1;

  WavWriter recorder("output.wav", numberOfFrames);

  for (int i = 0; i < numberOfFrames; ++i) {
    double y = osc.tick();
    recorder.write(y);
  }

  return 0;
}
