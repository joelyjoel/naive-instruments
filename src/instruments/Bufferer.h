#pragma once

#include "../core.h"

/**
 * Pass through instrument which writes to an internal buffer.
 */
class Bufferer : public NaiveInstrument<double> {
private:
  MonoBuffer buffer;
  int i = 0;
  int maxSize;

public:
  Socket<double> &input = addSocket<double>();

public:
  Bufferer(int maxSize) : buffer(maxSize), maxSize(maxSize) { reset(); }

  double tick() override {
    double signal = input();
    if (i < maxSize)
      buffer[i] = signal;
    ++i;
    return signal;
  }

  void reset() { i = 0; }

  MonoBuffer *copyBuffer() { return buffer.slice(0, i); }
};
