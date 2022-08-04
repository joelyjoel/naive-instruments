#pragma once

#include "../lib.h"

class WaveformBufferer {
private:
  BufferWriter bufferer;
  ZeroCrossingDetector detector;
  BangAwaiter waiter;

  Signal<double> *input;

  void assemble() { waiter << detector << bufferer; }

public:
  WaveformBufferer() : bufferer(4096) { assemble(); }

public:
  int minNumberOfFrames = 0;

private:
  int index = -1;
  MonoBuffer *copyNextWaveform() {
    do {
      bufferer.reset();
      waiter.next();
    } while (bufferer.currentSize() < minNumberOfFrames);
    ++index;
    return bufferer.copyBuffer();
  }

  void skipNextWaveform() {
    do {
      bufferer.reset();
      waiter.next();
    } while (bufferer.currentSize() < minNumberOfFrames);
    ++index;
  }

  void reset() {
    bufferer.reset();
    detector.reset();
    input->reset();
  }

  void skipTo(int destinationIndex) {
    if (destinationIndex < index)
      reset();
    while (index < destinationIndex)
      skipNextWaveform();
  }

public:
  MonoBuffer *select(int waveformIndex) {
    skipTo(waveformIndex);
    return copyNextWaveform();
  }

  MonoBuffer *operator[](int waveformIndex) { return select(waveformIndex); }

  Signal<double> &operator<<(Signal<double> &inputSignal) {
    input = &inputSignal;
    return bufferer << inputSignal;
  }
};
