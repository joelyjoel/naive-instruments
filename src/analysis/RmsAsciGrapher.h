#pragma once

#include "../lib.h"
#include "./RMS.h"
#include <iostream>
#include <string>

class RmsAsciGraph {
  const std::string charsInAscendingOrderOfLoudness = " -~sS#%!";

public:
  void fromFile(std::ostream &out, const std::string &filePath,
                int width = 80) {
    WavReader file(filePath);
    Sampler sampler(filePath);

    RMS loudness;
    loudness.windowSize = file.numberOfFrames() / width;

    loudness << sampler;

    for (int window = 0; window < width; ++window) {
      double rms = loudness.nextWindow();
      int index = int(rms * float(charsInAscendingOrderOfLoudness.length()));

      char c = charsInAscendingOrderOfLoudness[c];
      out << charsInAscendingOrderOfLoudness.substr(index, 1);
    }
  }
};
