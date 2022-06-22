#include "Units.h"

#include "../core.h"

class EvaluateUnits {
public:
  struct EvaluateTimeContext {};

public:
  /**
   * Evaluates a parsed time as millseconds.
   */
  static float time(float n, Units::Unit unit,
                    EvaluateTimeContext *ctx = nullptr) {
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
