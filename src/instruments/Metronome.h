#include "../core.h"

class Metronome : public Signal<bool> {
public:
  SignalInput<double> &bpm = addInput<double>("bpm/bpm");

private:
  const double k = 1.0 / (60.0 * sampleRate);
  double progress = 0;

protected:
  void action() override {
    progress += bpm() * k;
    if (progress >= 1) {
      out(true);
      do {
        progress -= 1;
      } while (progress >= 1);
    } else
      out(false);
  }
};
