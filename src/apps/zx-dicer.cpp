#include "../cli/CommandLineArguments.h"
#include "../lib.h"
#include <iostream>
#include <string>

// TODO: Refactor as class

class ZXDicer {
private:
  const std::string &inputFilePath;
  const std::string &outputPath;
  Sampler sampler;
  ZeroCrossingDetector detector;

  const int maxWaveformLength = 4096;
  int currentWaveformLength;
  void resetCurrentBuffer() { currentWaveformLength = 0; }
  MonoBuffer buffer;
  double currentWaveformPeak() { return buffer.peak(0, currentWaveformLength); }
  void normaliseCurrentWaveform() {
    double peak = currentWaveformPeak();
    buffer /= peak;
  }
  int waveformIndex;

  void writeCurrentWaveform() {
    const std::string &filename =
        outputPath + "/waveform" + std::to_string(waveformIndex) + ".wav";
    WavWriter output(filename, currentWaveformLength);
    for (int j = 0; j < currentWaveformLength; ++j)
      output << buffer[j];

    std::cout << "Written to " << filename << "\n";
  }

public:
  ZXDicer(const std::string &inputFilePath, const std::string &outputPath)
      : inputFilePath(inputFilePath), sampler(inputFilePath),
        outputPath(outputPath), buffer(maxWaveformLength) {

    detector << sampler;
    resetCurrentBuffer();
    waveformIndex = 0;
  }

private:
  int internalClock = -1;
  void tick() {
    ++internalClock;
    double signal = sampler[internalClock];

    if (currentWaveformLength < maxWaveformLength)
      buffer[currentWaveformLength++] = signal;

    bool atZeroCrossing = detector[internalClock];
    if (atZeroCrossing)
      handleZeroCrossing();
  }

private:
  void handleZeroCrossing() {
    if (currentWaveformPeak() < 0.01)
      std::cout << "Waveform " << waveformIndex << " is too quiet\n";
    else if (currentWaveformLength < 100)
      std::cout << "Waveform " << waveformIndex << " is too short\n";
    else {
      normaliseCurrentWaveform();
      writeCurrentWaveform();
    }

    ++waveformIndex;
    resetCurrentBuffer();
  }

private:
  void go() {
    for (int i = 0; i < sampler.numberOfFrames(); ++i)
      tick();
  }

public:
  static int main(int argc, char **argv) {
    CommandLineArguments args(argc, argv);
    std::cout << args["o"] << "\n";

    ZXDicer dicer(args[0], args["o"]);
    dicer.go();

    return 0;
  }
};
