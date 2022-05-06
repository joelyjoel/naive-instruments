#include "./makeASawToothWave.h"
#include "Add.h"
#include "WavWriter.h"
#include <iostream>
#include <ostream>

int main() {
  // double *buffer = record1SecondSawtoothWave();

  Sawtooth osc(200), osc2(250);
  Add sum(&osc, &osc2);
  const int numberOfFrames = sampleRate * 1;

  WavWriter recorder("output.wav", numberOfFrames);

  std::cout << "Recording...\n";
  for (int i = 0; i < numberOfFrames; ++i) {
    double y = ++sum;
    recorder.write(y * .5);
  }
  std::cout << "Finished recording.\n";

  return 0;
}
