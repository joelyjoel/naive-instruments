
#include "writeAudioFile.h"
#include <sndfile.h>

void writeAudioFile(const std::string &filename, Sample<double> &sample) {
  SndfileHandle file(filename, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_FLOAT,
                     sample.numberOfChannels, sample.sampleRate);
  file.write(sample.dataptr(), sample.numberOfSamples());
}
