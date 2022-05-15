#pragma once

#include "../core.h"

#include <iostream>
#include <string>
#include <vector>

class RMSTracker {
  const int windowSize;

  int frameWithinCurrentWindow = 0;
  double currentWindowSum = 0;
  double max = 0;

public:
  RMSTracker(double windowDuration = .001)
      : windowSize(windowDuration * sampleRate) {}
  std::vector<double> intensityData;

private:
  void write(double sample) {
    currentWindowSum += sample * sample;
    ++frameWithinCurrentWindow;
    if (frameWithinCurrentWindow == windowSize) {
      double rms = sqrt(currentWindowSum / float(windowSize));
      intensityData.push_back(rms);
      frameWithinCurrentWindow = 0;
      currentWindowSum = 0;

      if (rms > max)
        max = rms;
    }
  }

public:
  void operator<<(double sample) { write(sample); }

  void waveform(std::ostream &output) {
    std::string charCresc = " -~+*=%#@$!";
    for (int i = 0; i < intensityData.size(); ++i) {
      int intensityIndex = charCresc.length() * (intensityData[i]);
      output << charCresc[intensityIndex];
    }
  }
};
