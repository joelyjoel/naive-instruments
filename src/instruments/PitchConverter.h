#include "../core.h"

class IntervalToRatio : public Signal<double> {
public:
  SignalInput<double> &interval = addInput<double>();

  void action() { out(pow(2.0, (interval() / 12.0))); }
};

class PitchConverter : public Signal<double> {
public:
  SignalInput<double> &pitch = addInput<double>();

  void action() { out(440 * pow(2.0, ((pitch() - 69) / 12.0))); }
};
