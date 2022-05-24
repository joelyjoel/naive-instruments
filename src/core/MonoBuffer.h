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
  MonoBuffer(double *dataPtr, int length) : numberOfSamples(length) {
    data = dataPtr;
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

  double peak() {
    double max = 0;
    for (int i = 0; i < numberOfSamples; ++i)
      if (abs(data[i]) > max)
        max = abs(data[i]);
    return max;
  }

  void scale(double scaleFactor) {
    for (int i = 0; i < numberOfSamples; ++i)
      data[i] *= scaleFactor;
  }

  void operator*=(double scaleFactor) { scale(scaleFactor); }
  void operator/=(double scaleFactor) { scale(1.0 / scaleFactor); }

  MonoBuffer view(int from = 0, int until = 0) {
    if (until <= 0)
      until = numberOfSamples - until;
    return MonoBuffer(data + from, until - from);
  }

  MonoBuffer *slice(int from = 0, int until = 0) {
    return view(from, until).copy();
  }
  MonoBuffer *copy() {
    MonoBuffer *newbuffer = new MonoBuffer(numberOfSamples);
    for (int i = 0; i < numberOfSamples; ++i)
      newbuffer->data[i] = data[i];
    return newbuffer;
  }

  void normalise() { scale(1.0 / peak()); }
};
