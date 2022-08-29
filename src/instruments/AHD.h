#pragma once
#include "../core.h"
class AHD : public Signal<double> {
public:
  SignalInput<double> attack{this, "attack/s"};
  SignalInput<double> hold{this, "hold/s"};
  SignalInput<double> decay{this, "decay/s"};

private:
  enum AHDStage { A, H, D, finished };
  double phase = 0;
  AHDStage stage = A;

  void action() {

    switch (stage) {

    case A:
      phase += 1 / sampleRate / attack();
      if (phase >= 1) {
        phase = 0;
        stage = H;
      }
      out(phase);
      break;

    case H:
      phase += 1 / sampleRate / hold();
      if (phase >= 1) {
        phase = 0;
        stage = D;
      }
      out(1);
      break;

    case D:
      phase += 1 / sampleRate / decay();
      if (phase >= 1) {
        phase = 0;
        stage = finished;
      }
      out(1 - phase);
      break;

    case finished:
      out(0);
      break;
    }
  }
};
