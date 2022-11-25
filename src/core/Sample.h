#include <algorithm>
#include <memory>

template <typename T> class Sample {
  int numberOfFrames;
  int numberOfChannels;
  T *data;
  float sampleRate;

public:
  Sample(int numberOfChannels, int numberOfFrames, float sampleRate = 44100)
      : numberOfChannels(numberOfChannels), numberOfFrames(numberOfFrames),
        sampleRate(sampleRate) {

    data = new T[numberOfChannels * numberOfFrames];
  }

  ~Sample() { delete data; }

private:
  /**
   * Get a reference to a specific cell of the sample data.
   */
  T &cell(int channel, int frame) {
    // TODO: add bounds checks
    if (frame < 0 || frame >= numberOfFrames)
      throw 1; // TODO: Use proper exception
    else if (channel < 0 || channel >= numberOfChannels)
      throw 1; // TODO: Use proper exception

    return data[frame * numberOfChannels + channel];
  }

  // TODO: Define an iterator through a region of neighboring data

public:
  T read(int channel, int frame) { return cell(channel, frame); }
  void write(int channel, int frame, T y) { cell(channel, frame) = y; }

  int frameAtTime(float t) { return t * sampleRate; }

  //
  // Metrics
  //

  float duration() { return float(numberOfFrames) / sampleRate; }

  T peak(float t0 = 0, float t1 = 0) {
    if (t1 == 0)
      t1 = duration();

    int frame0 = frameAtTime(t0);
    int frame1 = frameAtTime(t1);
    T max = read(0, frame0);
    for (int c = 0; c < numberOfChannels; ++c)
      for (int frame = frame0; frame < frame1; ++frame)
        max = std::max(max, read(c, frame));
  }

  static Sample<T> concat(Sample<T> &a, Sample<T> &b) {
    if (a.sampleRate != b.sampleRate)
      throw 1; // TODO: Use proper exception
    int numberOfChannels = std::max(a.numberOfChannels, b.numberOfChannels);
    int numberOfFrames = a.numberOfFrames + b.numberOfFrames;
    std::shared_ptr<Sample<T>> sample =
        std::make_shared<Sample<T>>(numberOfChannels, numberOfFrames);
  }
};
