#include "../core.h"

class Decay : public Signal<double> {
private:
  double phase = 0;

public:
  SignalInput<double> duration{
      this,
      "duration/s",
  };

protected:
  void action() override {
    if (phase < 1.0) {
      phase += (1.0 / 44100.0) / duration();
      out(1.0 - phase);
    } else
      out(0.0);
  }
};
