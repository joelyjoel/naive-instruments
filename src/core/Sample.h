#include <algorithm>
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>

template <typename T> class Sample {

  int numberOfFrames;
  int numberOfChannels;
  T *data;

public:
  Sample(int numberOfFrames, int numberOfChannels = 1)
      : numberOfChannels(numberOfChannels), numberOfFrames(numberOfFrames) {
    data = new T[numberOfChannels * numberOfFrames];
  }

  Sample(std::vector<T> _data, int numberOfChannels = 1)
      : Sample(_data.size(), numberOfChannels) {
    for (int i = 0; i < _data.size(); ++i)
      data[i] = _data[i];
  }

  ~Sample() { delete data; }

private:
  /**
   * Get a reference to a specific cell of the sample data.
   */
  T &cell(int channel, int frame) {
    // TODO: add bounds checks
    if (frame < 0 || frame >= numberOfFrames) {
      std::cerr << "frame out of bounds: " << frame << "\n";
      throw 1; // TODO: Use proper exception
    } else if (channel < 0 || channel >= numberOfChannels) {
      std::cerr << "channel out of bonuds: " << channel << "\n";
      throw 1; // TODO: Use proper exception
    }

    return data[frame * numberOfChannels + channel];
  }

  // TODO: Define an iterator through a region of neighboring data

public:
  T read(int frame, int channel = 0) { return cell(channel, frame); }

  T readWithInterpolation(float frame, int channel = 0) {
    // (linear interpolation between samples)
    float progress = fmod(frame, 1);
    if (progress == 0)
      return read(int(frame), channel);
    T before = read(int(frame), channel);
    T after = read(int(frame + 1), channel);
    return (1.0 - progress) * before + progress * after;
  }

  /**
   * Overwrite a single cell
   */
  void write(T y, int frame, int channel = 0) { cell(channel, frame) = y; }

  /**
   * Overwrite a region using another sample
   */
  void write(Sample<T> &y, int offset = 0) {
    // TODO: Support channel offset
    for (int c = 0; c < y.numberOfChannels; ++c)
      for (int readFrame = 0; readFrame < y.numberOfFrames; ++readFrame) {
        int writeFrame = readFrame + offset;
        if (writeFrame >= 0 && writeFrame < numberOfFrames)
          write(y.read(readFrame, c), writeFrame, c);
      }
  }

  void mix(T y, int frame = 0, int channel = 0) { cell(channel, frame) += y; }

  void mix(Sample<T> &y, int offset = 0) {
    for (int c = 0; c < y.numberOfChannels; ++c)
      for (int readFrame = 0; readFrame < y.numberOfFrames; ++readFrame) {
        int writeFrame = readFrame + offset;
        if (writeFrame >= 0 && writeFrame < numberOfFrames)
          mix(y.read(readFrame, c), writeFrame, c);
      }
  }

  T peak(int frame0 = 0, int frame1 = 0) {
    if (frame1 == 0)
      frame1 = numberOfFrames;

    T max = read(frame0, 0);
    for (int c = 0; c < numberOfChannels; ++c)
      for (int frame = frame0; frame < frame1; ++frame)
        max = std::max(max, read(frame, c));
    return max;
  }

  T rms(int frame0 = 0, int frame1 = 0) {
    if (frame1 == 0)
      frame1 = numberOfFrames;

    T sum = 0;
    for (int frame = frame0; frame < frame1; ++frame)
      for (int channel = 0; channel < numberOfChannels; ++channel) {
        T y = read(frame, channel);
        sum += y * y;
      }

    int n = (frame1 - frame0) * numberOfChannels;
    return sqrt(sum / n);
  }

  std::shared_ptr<Sample<T>> slice(int frame0 = 0, int frame1 = 0) {
    if (frame1 == 0)
      frame1 = numberOfFrames;

    int lengthOfNewSample = frame1 - frame0;

    auto sample =
        std::make_shared<Sample<T>>(lengthOfNewSample, numberOfChannels);

    for (int writeFrame = 0; writeFrame < lengthOfNewSample; ++writeFrame) {
      int readFrame = writeFrame + frame0;
      for (int channel = 0; channel < numberOfChannels; ++channel)
        sample->write(read(readFrame, channel), writeFrame, channel);
    }

    return sample;
  }

  // TODO: writing wav files
  // TODO: Reading wav files

  std::shared_ptr<Sample<T>>
  selectChannels(std::vector<int> &channelsToSelect) {
    auto newSample =
        std::make_shared<Sample<T>>(numberOfFrames, channelsToSelect.size());
    for (int writeChannel = 0; writeChannel < channelsToSelect.size();
         ++writeChannel)
      for (int frame = 0; frame < numberOfFrames; ++frame)
        newSample->write(read(frame, channelsToSelect[writeChannel]), frame,
                         writeChannel);
    return newSample;
  }

  std::shared_ptr<Sample<T>> selectChannel(int channel) {
    std::vector<int> channels = {channel};
    return selectChannels(channels);
  }

  static std::shared_ptr<Sample<T>> concat(Sample<T> &a, Sample<T> &b) {
    int numberOfChannels = std::max(a.numberOfChannels, b.numberOfChannels);
    int numberOfFrames = a.numberOfFrames + b.numberOfFrames;
    std::shared_ptr<Sample<T>> sample =
        std::make_shared<Sample<T>>(numberOfFrames, numberOfChannels);

    // TODO: add configurable crossfades

    sample->write(a, 0);
    sample->write(b, a.numberOfFrames);
    return sample;
  }
};
