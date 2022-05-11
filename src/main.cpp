#include "./makeASawToothWave.h"
#include "Add.h"
#include "BreakpointEnvelope.h"
#include "Osc.h"
#include "WavWriter.h"
#include "Waveforms.h"
#include "Wavetable.h"
#include <iostream>
#include <ostream>

int main() {

  BreakpointEnvelope envelope;
  for (int i = 0; i < 4; ++i) {
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .1);
    envelope.addSection(400, 0, .3);
    envelope.addSection(400, 0, .3);
    envelope.addSection(400, 0, .2);
  }

  Osc signal(200, Waveforms::sine());
  signal.frequency = envelope;

  const int numberOfFrames = sampleRate * envelope.duration();
  WavWriter recorder("output.wav", numberOfFrames);

  std::cout << "Recording...\n";
  for (int i = 0; i < numberOfFrames; ++i) {
    double y = ++signal;
    recorder.write(y * .5);
  }
  std::cout << "Finished recording.\n";

  return 0;
}
