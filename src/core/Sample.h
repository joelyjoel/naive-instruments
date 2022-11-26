#include "./SampleData.h"
#include <algorithm>

template <typename T> class Sample {
  float sampleRate;
  SampleData<T> data;

  static constexpr const float defaultSampleRate = 44100;

  Sample(float duration, int numberOfChannels,
         float sampleRate = defaultSampleRate)
      : data(duration * sampleRate, numberOfChannels), sampleRate(sampleRate) {}

  Sample(std::vector<T> _data, int numberOfChannels,
         float sampleRate = defaultSampleRate)
      : data(data, numberOfChannels), sampleRate(sampleRate) {}

  int numberOfFrames() { return data.numberOfFrames; }
  int numberOfChannels() { return data.numberOfChannels; }
  int frameAtT(float t) { return t * sampleRate; }
  float duration() { return float(numberOfFrames) / sampleRate; }

  T read(float t, int channel = 0) {
    return data.readWithInterpolation(frameAtT(t), channel);
  }

  void write(T y, float t, int channel = 0) {
    data.write(y, frameAtT(t), channel);
  }

  void mix(SampleData<T> &y, float offset) {
    if (sampleRate != y.sampleRate)
      throw 1;
    data.mix(y, offset * sampleRate);
  }

  T peak(float t0 = 0, float t1 = 0) {
    if (t1 == 0)
      t1 == duration();
    data.peak(frameAtT(t0) < frameAtT(t1));
  }

  T rms(float t0 = 0, float t1 = 0) {
    if (t1 == 0)
      t1 == duration();
    data.rms(frameAtT(t0) < frameAtT(t1));
  }

  std::shared_ptr<Sample<T>> slice(float t0, float t1) {
    if (t1 == 0)
      t1 == duration();
    // TODO: You aren't handling memory right here
    return Sample(data.slice(frameAtT(t0), frameAtT(t1)), sampleRate);
  }
};
