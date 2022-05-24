#pragma once

#include "../core.h"

class BufferWriter : public NaiveInstrument<double> {
public:
  Socket<double> &input = addSocket<double>();

private:
  MonoBuffer *buffer;

public:
  BufferWriter(int bufferSize) { buffer = new MonoBuffer(bufferSize); }
  ~BufferWriter() {
    if (buffer != nullptr)
      delete buffer;
    buffer = nullptr;
  }

private:
  int writeHead = 0;

public:
  double tick() {
    double signal = input();
    if (writeHead < buffer->numberOfFrames())
      (*buffer)[writeHead] = signal;
    ++writeHead;
    return signal;
  }

  int currentSize() { return writeHead; }
  MonoBuffer *copyBuffer() { return buffer->slice(0, currentSize()); }

  void reset() { writeHead = 0; }

  MonoBuffer *copyAndReset() {
    auto ptr = copyBuffer();
    reset();
    return ptr;
  }
};
