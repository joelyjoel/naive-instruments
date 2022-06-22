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
    case Units::samples:
      return n / float(sampleRate);
    default:
      throw CantHandleUnit;
    }
  }
};
