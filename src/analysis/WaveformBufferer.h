#pragma once

#include "../lib.h"

class WaveformBufferer {
private:
  shared_ptr<BufferWriter> bufferer;
  shared_ptr<ZeroCrossingDetector> detector =
      make_shared<ZeroCrossingDetector>();
  BangAwaiter waiter;

  shared_ptr<FrameStream<double>> input;

  void assemble() {
    waiter << detector;
    detector->input << bufferer;
  }

public:
  WaveformBufferer() {
    bufferer = make_shared<BufferWriter>(4096);
    assemble();
  }

public:
  int minNumberOfFrames = 0;

private:
  int index = -1;
  MonoBuffer *copyNextWaveform() {
    do {
      bufferer.reset();
      waiter.next();
    } while (bufferer->currentSize() < minNumberOfFrames);
    ++index;
    return bufferer->copyBuffer();
  }

  void skipNextWaveform() {
    do {
      bufferer.reset();
      waiter.next();
    } while (bufferer->currentSize() < minNumberOfFrames);
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

  void operator<<(shared_ptr<FrameStream<double>> inputSignal) {
    bufferer->input << inputSignal;
  }
};
