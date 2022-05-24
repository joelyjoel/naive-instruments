#pragma once

#include "../core.h"

class RMS {
private:
  NaiveInstrument<double> *signal;

public:
  void operator<<(NaiveInstrument<double> &input) { signal = &input; }

public:
  RMS() {}
  RMS(unsigned int windowSize) : windowSize(windowSize) {}

  unsigned int windowSize = sampleRate / 1000;

  double nextWindow() {
    sum = 0;
    sampleSize = 0;
    for (int i = 0; i < windowSize; ++i)
      readNextFrame();
    return rms();
  }

private:
  double sum = 0;
  unsigned int sampleSize = 0;
  int internalClock = 0;

  void readNextFrame() {
    double x = (*signal)[internalClock++];
    sum += x * x;
    ++sampleSize;
  }

  double rms() { return sqrt(sum / sampleSize); }
};
