#pragma once
#include "../core.h"
class AHD : public Signal<double> {
public:
  SignalInput<double> &attack = addInput<double>("attack/s", 1);
  SignalInput<double> &hold = addInput<double>("hold/s", 1);
  SignalInput<double> decay = addInput<double>("decay/s", 1);

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
