#pragma once

#include "LazyRegex.h"
#include <string>
using std::string;

class Units {
public:
  typedef enum { Time = 1, Frequency, Ratio } Domain;

  typedef enum {
    unknownUnit = -1,
    noUnit = 0,

    // Time
    seconds = Time * 100,
    milliseconds,
    minutes,
    hours,
    crotchets,
    samples,
    zeroCrossings,

    // Frequency
    Hz = Frequency * 100,
    bpm,
    /** Midi pitch number */
    midi,

    // ratio
    percent = Ratio * 100,
    octaves,
    semitones,
    decibels,

  } Unit;

public:
  static Unit parse(const string &str) {
    if (str == "")
      return noUnit;
    else if (str == "s" || str == "seconds")
      return seconds;
    else if (str == "ms" || str == "milliseconds")
      return milliseconds;
    else if (str == "min" || str == "minutes")
      return minutes;
    else if (str == "h" || str == "hours")
      return hours;
    else if (str == "smp")
      return samples;
    else if (str == "zx")
      return zeroCrossings;
    else if (str == "Hz" || str == "hertz")
      return Hz;
    else if (str == "bpm")
      return bpm;
    else if (str == "midi")
      return midi;
    else if (str == "octave" || str == "octaves")
      return octaves;
    else if (str == "st")
      return semitones;
    else if (str == "%")
      return percent;

    else
      return unknownUnit;
  }

  static LazyRegex pattern;
};
