#include "./readAudioFile.h"
#include <iostream>
#include <memory>

std::shared_ptr<Sample<double>> readAudioFile(const std::string &filename) {

  SndfileHandle file;
  file = SndfileHandle(filename);

  // Create the container
  std::shared_ptr<Sample<double>> sample = std::make_shared<Sample<double>>(
      file.frames(), file.channels(), file.samplerate());

  double buffer[file.frames()];

  // TODO: Use bigger chunks
  for (int frame = 0; frame < file.frames(); ++frame) {
    int numberRead = file.readf(buffer, 1);
    for (int channel = 0; channel < file.channels(); ++channel) {
      sample->write(buffer[channel], frame, channel);
    }
  }

  return sample;
}
