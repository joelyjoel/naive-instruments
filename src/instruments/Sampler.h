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
  void action() override {
    if (playhead < 0) {
      ++playhead;
      out(0);
    } else if (playhead < buffer->numberOfFrames())
      out((*buffer)[++playhead]);
    else
      out(0);
  }

protected:
  void resetState() override { playhead = 0; }

public:
  void skipTo(int frame) { playhead = frame; }

public:
  int numberOfFrames() { return buffer->numberOfFrames(); }
};
