#include "./makeASawToothWave.h"
#include "Add.h"
#include "Osc.h"
#include "WavWriter.h"
#include "Waveforms.h"
#include "Wavetable.h"
#include <iostream>
#include <ostream>

const int numberOfFrames = sampleRate * 1;

int main() {

  Osc signal(200, Waveforms::sine());

  WavWriter recorder("output.wav", numberOfFrames);

  std::cout << "Recording...\n";
  for (int i = 0; i < numberOfFrames; ++i) {
    double y = ++signal;
    recorder.write(y * .5);
  }
  std::cout << "Finished recording.\n";

  return 0;
}
