#pragma once

#include "../core.h"

class FixedPipe : public Signal<double> {
  double *buffer;
  int bufferSize;
  int tapeHeadIndex = 0;

public:
  SignalInput<double> &input = addSocket<double>();

  FixedPipe(double duration) : bufferSize(duration * sampleRate) {
    buffer = new double[bufferSize];
  }
  ~FixedPipe() { delete buffer; }

  double tick() {
    buffer[tapeHeadIndex] = input();
    std::cout << input() << "\n";

    ++tapeHeadIndex;
    if (tapeHeadIndex >= bufferSize)
      tapeHeadIndex -= bufferSize;

    std::cout << tapeHeadIndex << " " << buffer[tapeHeadIndex] << "\n";
    return buffer[tapeHeadIndex];
  }

  std::string label() { return "FixedPipe"; }
};
