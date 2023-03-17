#include "../core.h"

class Decay : public FrameStream<double> {
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
      writeFrame(1.0 - phase);
    } else
      writeFrame(0.0);
  }

public:
  void resetState() override { phase = 0; }
};
