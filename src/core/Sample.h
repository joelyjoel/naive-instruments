#include <algorithm>
#include <memory>

template <typename T> class Sample {

  int numberOfFrames;
  int numberOfChannels;
  T *data;
  float sampleRate;

public:
  Sample(int numberOfFrames, int numberOfChannels = 1, float sampleRate = 44100)
      : numberOfChannels(numberOfChannels), numberOfFrames(numberOfFrames),
        sampleRate(sampleRate) {
    data = new T[numberOfChannels * numberOfFrames];
  }

  Sample(std::vector<T> _data, int numberOfChannels = 1,
         float sampleRate = 44100)
      : Sample(_data.size(), numberOfChannels, sampleRate) {
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
    if (frame < 0 || frame >= numberOfFrames)
      throw 1; // TODO: Use proper exception
    else if (channel < 0 || channel >= numberOfChannels)
      throw 1; // TODO: Use proper exception

    return data[frame * numberOfChannels + channel];
  }

  // TODO: Define an iterator through a region of neighboring data

public:
  T read(int frame, int channel = 0) { return cell(channel, frame); }

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

  int frameAtTime(float t) { return t * sampleRate; }

  float duration() { return float(numberOfFrames) / sampleRate; }

  T peak(float t0 = 0, float t1 = 0) {
    if (t1 == 0)
      t1 = duration();

    int frame0 = frameAtTime(t0);
    int frame1 = frameAtTime(t1);
    T max = read(frame0, 0);
    for (int c = 0; c < numberOfChannels; ++c)
      for (int frame = frame0; frame < frame1; ++frame)
        max = std::max(max, read(frame, c));
    return max;
  }

  static std::shared_ptr<Sample<T>> concat(Sample<T> &a, Sample<T> &b) {
    if (a.sampleRate != b.sampleRate)
      throw 1; // TODO: Use proper exception
    int numberOfChannels = std::max(a.numberOfChannels, b.numberOfChannels);
    int numberOfFrames = a.numberOfFrames + b.numberOfFrames;
    std::shared_ptr<Sample<T>> sample = std::make_shared<Sample<T>>(
        numberOfFrames, numberOfChannels, a.sampleRate);

    // TODO: add configurable crossfades

    sample->write(a, 0);
    sample->write(b, a.numberOfFrames);
    return sample;
  }

  // TODO: rms
  // TODO: writing wav files
  // TODO: Reading wav files
  // TODO: selectChannels
};
