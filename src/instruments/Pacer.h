#include "../lib.h"

class Pacer : public Signal<double> {

public:
  SignalInput<double> input{this, "input"};
  SignalInput<double> rate{this, "rate"};

private:
  float t = 0;
  float phase = 0;
  double a, b;

  void syncInputs() override {}

public:
  void action() override {
    rate.sync(internalClock);
    t += rate();

    input.sync(floor(t));
    a = input();

    // FIXME: Bug when rate goes below 1.0
    input.sync(ceil(t));
    b = input();

    phase = fmod(t, 1.0);

    out(b * phase + a * (1.0 - phase));
  }
};
