#pragma once

#include "../core.h"

class FixedPipe : public FrameStream<double> {
  double *buffer;
  int bufferSize;
  int tapeHeadIndex = 0;

public:
  FrameStreamConsumer<double> input{this, "input"};

  FixedPipe(double duration) : bufferSize(duration * sampleRate) {
    buffer = new double[bufferSize];
  }
  ~FixedPipe() { delete buffer; }

  void action() {
    buffer[tapeHeadIndex] = input.readFrame();
    std::cout << input.readFrame() << "\n";

    ++tapeHeadIndex;
    if (tapeHeadIndex >= bufferSize)
      tapeHeadIndex -= bufferSize;

    std::cout << tapeHeadIndex << " " << buffer[tapeHeadIndex] << "\n";
    writeFrame(buffer[tapeHeadIndex]);
  }

  std::string label() { return "FixedPipe"; }
};
