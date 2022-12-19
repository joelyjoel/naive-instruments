#pragma once

#include "./Sample.h"
#include <memory>

template <typename T> class Region : ReadableSample<T> {
private:
  std::shared_ptr<ReadableSample<T>> underlyingSample;
  float startAt;
  float duration;

public:
  Region(std::shared_ptr<ReadableSample<T>> underlyingSample, float startAt,
         float duration)
      : startAt(startAt), duration(duration),
        underlyingSample(underlyingSample) {}

  T read(double time, int channel = 0) override {
    // TODO: Check if within fade in/out
    if (time < duration) {
      int f = (time + startAt) * underlyingSample->sampleRate();
      return underlyingSample.readByFrame(f, channel);
    } else
      return 0;
  };
  T readByFrame(int frame, int channel = 0) override;
};
