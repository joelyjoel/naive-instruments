#include "../core.h"

class Metronome : public FrameStream<bool> {
public:
  SignalInput<double> bpm{this, "bpm/bpm"};

private:
  const double k = 1.0 / (60.0 * sampleRate);
  double progress = 0;

protected:
  void action() override {
    progress += bpm.readFrame() * k;
    if (progress >= 1) {
      writeFrame(true);
      do {
        progress -= 1;
      } while (progress >= 1);
    } else
      writeFrame(false);
  }
};
