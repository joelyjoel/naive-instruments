#include "./makeASawToothWave.h"
#include "Add.h"
#include "WavWriter.h"
#include "Waveforms.h"
#include "Wavetable.h"
#include <iostream>
#include <ostream>

int main() {

  UnsignedSaw spinner;
  spinner.frequency = 440.0;

  Wavetable signal;
  signal.phase = spinner;

  const int numberOfFrames = sampleRate * 1;

  MonoBuffer &squareWave = Waveforms::square();

  WavWriter recorder("output.wav", numberOfFrames);

  std::cout << "Recording...\n";
  for (int i = 0; i < numberOfFrames; ++i) {
    double y = ++signal;
    recorder.write(y * .5);
  }
  std::cout << "Finished recording.\n";

  return 0;
}
