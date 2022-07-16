#pragma once

#include "core.h"
#include "file-io/WavReader.h"
#include <math.h>

class Waveforms {
public:
  static MonoBuffer &square() {
    MonoBuffer &buffer = *(new MonoBuffer(44100));
    for (int i = 0; i < buffer.numberOfSamples; ++i)
      buffer.data[i] = i * 2 > buffer.numberOfSamples ? -1.0 : 1.0;
    return buffer;
  }

  static MonoBuffer &sine() {
    MonoBuffer &buffer = *(new MonoBuffer(44100));
    for (int i = 0; i < buffer.numberOfSamples; ++i)
      buffer.data[i] = sin(M_PI * 2 * i / 44100.0);
    return buffer;
  }

  static MonoBuffer &saw() {
    MonoBuffer &buffer = *(new MonoBuffer(44100));
    for (int i = 0; i < buffer.numberOfSamples; ++i)
      buffer.data[i] = float(i) / float(buffer.numberOfSamples) * 2 - 1;
    return buffer;
  }

  static MonoBuffer &triangle() {
    MonoBuffer &buffer = *(new MonoBuffer(44100));
    for (int i = 0; i < buffer.numberOfSamples; ++i) {
      double saw = float(i) / float(buffer.numberOfSamples) * 2 - 1;
      buffer.data[i] = abs(saw) * 2 - 1;
    }
    return buffer;
  }

  static MonoBuffer &fromFile(const std::string &filePath) {
    return *WavReader::readMonoFile(filePath);
  }

  static MonoBuffer &Malcolm01() {
    MonoBuffer &buffer = fromFile("wavetables/MALCOLM_01.wav");
    assert(buffer.numberOfFrames() == 162);
    return buffer;
  }

  static MonoBuffer &byName(const std::string &name) {
    if (name == "sin" || name == "sine")
      return sine();
    else if (name == "saw" || name == "sawtooth")
      return saw();
    else if (name == "tri" || name == "triangle")
      return triangle();
    else if (name == "sq" || name == "square")
      return square();
    else
      try {
        return fromFile("wavetables/" + name + ".wav");
      } catch (...) {
        std::cerr << "Couldn't find waveform called '" << name << "'\n";
        throw 1;
      }
  }
};
