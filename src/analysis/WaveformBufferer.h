#pragma once

#include "../lib.h"

class WaveformBufferer {
private:
  BufferWriter bufferer;
  ZeroCrossingDetector detector;
  BangAwaiter waiter;

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

  void skipTo(int destinationIndex) {
    while (index < destinationIndex)
      skipNextWaveform();
  }

public:
  MonoBuffer *select(int waveformIndex) {
    skipTo(waveformIndex);
    return copyNextWaveform();
  }

  NaiveInstrument<double> &operator<<(NaiveInstrument<double> &inputSignal) {
    return bufferer << inputSignal;
  }
};
