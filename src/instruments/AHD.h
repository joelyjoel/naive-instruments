#pragma once
#include "../core.h"
class AHD : public NaiveInstrument<double> {
public:
  Socket<double> &attack = addSocket<double>(1);
  Socket<double> &hold = addSocket<double>(1);
  Socket<double> decay = addSocket<double>(1);

private:
  enum AHDStage { A, H, D, finished };
  double phase = 0;
  AHDStage stage = A;

  double tick() {

    switch (stage) {

    case A:
      phase += 1 / sampleRate / attack();
      if (phase >= 1) {
        phase = 0;
        stage = H;
      }
      return phase;

    case H:
      phase += 1 / sampleRate / hold();
      if (phase >= 1) {
        phase = 0;
        stage = D;
      }
      return 1;

    case D:
      phase += 1 / sampleRate / decay();
      if (phase >= 1) {
        phase = 0;
        stage = finished;
      }
      return 1 - phase;

    case finished:
      return 0;
      break;
    }
  }
};
