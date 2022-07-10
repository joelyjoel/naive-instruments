#include "Units.h"

#include "../core.h"
#include "NumberWithUnit.h"

class EvaluateUnits {
public:
  struct EvaluateTimeContext {};

public:
  /**
   * Evaluates a parsed time as millseconds.
   */
  static Hopefully<float> time(const NumberWithUnit &n) {
    switch (n.unit) {
    case Units::noUnit:
    case Units::seconds:
      return n.number;
    case Units::milliseconds:
      return n.number * .001;
    case Units::minutes:
      return n.number * 60;
    case Units::hours:
      return n.number * 60 * 60;
    case Units::samples:
      return n.number / float(sampleRate);
    default:
      return Disappointment;
    }
  }

  static Hopefully<float> time(const NumberWithUnit &n, MonoBuffer &sample) {
    switch (n.unit) {
    case Units::samples:
      return n.number / float(sample.sampleRate);
    case Units::percent:
      return n.number * .01 * sample.duration();
    // TODO: Zero crossings
    default:
      return time(n);
    }
  }

  static Hopefully<float> frequency(const NumberWithUnit &n) {
    switch (n.unit) {
    case Units::noUnit:
    case Units::Hz:
      return n.number;
    case Units::bpm:
      return n.number / 60.0;
    default:
      return Disappointment;
    }
  }

  // TODO: Remove (duplicated by NumberWithUnit)
  static Hopefully<float> interval(const NumberWithUnit &n) {
    switch (n.unit) {
    case Units::noUnit:
    case Units::seconds:
      return n.number;
    case Units::bpm:
      return 1.0 / (n.number / 60.0);
    case Units::Hz:
      return 1.0 / n.number;
    case Units::milliseconds:
      return n.number * .001;
    case Units::minutes:
      return n.number * 60;
    case Units::hours:
      return n.number * 60 * 60;
    case Units::samples:
      return n.number / float(sampleRate);
    default:
      throw CantHandleUnit;
    }
  }

  static Hopefully<float> bpm(const NumberWithUnit &n) {
    Hopefully<float> f = frequency(n);
    if (f.success())
      return *f * 60.0;
    else
      return Disappointment;
  }

  static Hopefully<float> ratio(const NumberWithUnit &n) {
    switch (n.unit) {
    case Units::noUnit:
      return n.number;
    case Units::percent:
      return n.number * .01;
    case Units::semitones:
      return pow(2, n.number / 12.0);
    case Units::octaves:
      return pow(2, n.number);
    default:
      return Disappointment;
    }
  }
};
