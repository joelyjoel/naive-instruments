#pragma once

#include "core.h"
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
};
