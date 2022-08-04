#include "../core.h"

class IntervalToRatio : public Signal<double> {
public:
  Socket<double> &interval = addSocket<double>();

  double tick() { return pow(2.0, (interval() / 12.0)); }
};

class PitchConverter : public Signal<double> {
public:
  Socket<double> &pitch = addSocket<double>();

  double tick() { return 440 * pow(2.0, ((pitch() - 69) / 12.0)); }
};
