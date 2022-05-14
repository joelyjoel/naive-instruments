#include "record.h"

void record(const std::string &outputFile, NaiveInstrument<double> &signal,
            float duration) {

  double attenuation = .5;

  int numberOfFrames = duration * sampleRate;
  WavWriter recorder(outputFile, numberOfFrames);
  for (int i = 0; i < numberOfFrames; ++i) {
    recorder << signal[i] * attenuation;
  }
}
