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
  static float time(float n, Units::Unit unit) {
    switch (unit) {
    case Units::noUnit:
    case Units::seconds:
      return n;
    case Units::milliseconds:
      return n * .001;
    case Units::minutes:
      return n * 60;
    case Units::hours:
      return n * 60 * 60;
    case Units::samples:
      return n / float(sampleRate);
    default:
      throw CantHandleUnit;
    }
  }

  static float time(float n, Units::Unit unit, MonoBuffer &sample) {
    switch (unit) {
    case Units::samples:
      return n / float(sample.sampleRate);
    case Units::percent:
      return n * .01 * sample.duration();
    // TODO: Zero crossings
    default:
      return time(n, unit);
    }
  }

  static float frequency(NumberWithUnit &n) {
    switch (n.unit) {
    case Units::noUnit:
    case Units::Hz:
      return n.number;
    case Units::bpm:
      return n.number / 60.0;
    default:
      throw CantHandleUnit;
    }
  }

  static float interval(NumberWithUnit &n) {
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

  static float bpm(NumberWithUnit &n) {
    float f = frequency(n);
    return f * 60.0;
  }

  static float ratio(float n, Units::Unit unit) {
    switch (unit) {
    case Units::noUnit:
      return n;
    case Units::percent:
      return n * .01;
    case Units::semitones:
      return pow(2, n / 12.0);
    case Units::octaves:
      return pow(2, n);
    default:
      throw CantHandleUnit;
    }
  }
};
