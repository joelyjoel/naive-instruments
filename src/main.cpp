#include "./makeASawToothWave.h"
#include "Add.h"
#include "BreakpointEnvelope.h"
#include "Osc.h"
#include "WavWriter.h"
#include "Waveforms.h"
#include "Wavetable.h"
#include "record.h"
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

  record("output.wav", signal, 2);

  return 0;
}
