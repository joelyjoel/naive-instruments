#pragma once

#include "../core.h"
#include "../file-io/WavReader.h"
#include <iostream>

class Sampler : public Signal<double> {
private:
  MonoBuffer *buffer;
  int playhead = 0;

public:
  /**
   * deprecated
   * TODO: Remove and replace with static method.
   */
  Sampler(const std::string &filePath) {
    buffer = WavReader::readMonoFile(filePath);
  }

  Sampler(MonoBuffer &sharedBuffer) { buffer = &sharedBuffer; }

public:
  double tick() override {
    if (playhead < 0) {
      ++playhead;
      return 0;
    } else if (playhead < buffer->numberOfFrames())
      return (*buffer)[++playhead];
    else
      return 0;
  }

  void reset() override { playhead = 0; }

  void skipTo(int frame) { playhead = frame; }

public:
  int numberOfFrames() { return buffer->numberOfFrames(); }
};
