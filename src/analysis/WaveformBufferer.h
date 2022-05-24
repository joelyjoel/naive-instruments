#pragma once

#include "../lib.h"

class WaveformBufferer {
private:
  BufferWriter bufferer;
  ZeroCrossingDetector detector;
  BangAwaiter waiter;

  NaiveInstrument<double> *input;

  void assemble() { waiter << detector << bufferer; }

public:
  WaveformBufferer() : bufferer(4096) { assemble(); }

private:
  int index = 0;
  MonoBuffer *copyNextWaveform() {
    ++index;
    waiter.next();
    return bufferer.copyAndReset();
  }

  void skipNextWaveform() {
    ++index;
    waiter.next();
    bufferer.reset();
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

  NaiveInstrument<double> &operator<<(NaiveInstrument<double> &inputSignal) {
    input = &inputSignal;
    return bufferer << inputSignal;
  }
};
