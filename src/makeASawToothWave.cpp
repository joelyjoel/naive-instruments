#include "Osc.h"
#include <stdlib.h>

double *record1SecondSawtoothWave(double durationInSeconds) {
  int durationInSamples = durationInSeconds * sampleRate;

  Sawtooth osc(440);

  double *buffer = (double *)malloc(durationInSamples * sizeof(double));
  for (int i; i < durationInSamples; ++i) {
    buffer[i] = osc.tick();
  }

  return buffer;
}
