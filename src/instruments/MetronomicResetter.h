#include "../core.h"

class MetronomicResetter : public Signal<double> {
public:
  SignalInput<double> &input = addInput<double>();
  SignalInput<double> &bpm = addInput<double>();

private:
  const double k = 1.0 / (60.0 * sampleRate);
  double progress = 0;

public:
  void action() override {

    out(input());
    progress += bpm() * k;

    while (progress >= 1) {
      progress -= 1;
      input.reset();
    }
  }
};
