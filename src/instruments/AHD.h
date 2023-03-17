#pragma once
#include "../core.h"
class AHD : public FrameStream<double> {
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
      phase += 1 / sampleRate / attack.readFrame();
      if (phase >= 1) {
        phase = 0;
        stage = H;
      }
      writeFrame(phase);
      break;

    case H:
      phase += 1 / sampleRate / hold.readFrame();
      if (phase >= 1) {
        phase = 0;
        stage = D;
      }
      writeFrame(1);
      break;

    case D:
      phase += 1 / sampleRate / decay.readFrame();
      if (phase >= 1) {
        phase = 0;
        stage = finished;
      }
      writeFrame(1 - phase);
      break;

    case finished:
      writeFrame(0);
      break;
    }
  }
};
