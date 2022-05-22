#pragma once

#include <math.h>

class MonoBuffer {
public:
  const int numberOfSamples;
  int numberOfFrames() { return numberOfSamples; }
  double *data;

  MonoBuffer(int numberOfSamples) : numberOfSamples(numberOfSamples) {
    data = new double[numberOfSamples];
  }

  ~MonoBuffer() { delete data; }

  double &atIndex(int index) { return data[index % numberOfSamples]; }
  double &operator[](int index) { return atIndex(index); }
  double operator[](double index) { return interpolate(index); }

  double interpolate(double index) {
    int i0 = int(index);
    int i1 = (i0 + 1);
    float progress = index - float(i0);
    return atIndex(i0) * (1 - progress) + progress * atIndex(i1);
  }

  const float sampleRate = 44100;
  double duration() { return float(numberOfSamples) / float(sampleRate); }
  double atTime(double time) { return atIndex(time * sampleRate); }
  double operator()(double time) { return atTime(time); };
};
