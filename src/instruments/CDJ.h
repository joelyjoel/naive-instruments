#pragma once

#include "../core.h"
#include <iostream>

class CDJ : public Signal<double> {

public:
  SignalInput<double> input{this, "input"};
  float t = 0;

  double *internalBuffer;
  int bufferedUntil = 0;
  int lookAhead = 100; // samples
  int bufferSize = sampleRate * 60;

  CDJ() { internalBuffer = new double[bufferSize]; }

private:
  void action() override {
    if (paused)
      out(0.0);
    else {
      bufferMore();
      out(internalBuffer[int(t) % bufferSize]);
      ++t;
    }
  }

  void bufferMore() {
    while (bufferedUntil < t + lookAhead) {
      input.sync(bufferedUntil);
      internalBuffer[bufferedUntil % bufferSize] = input();
      ++bufferedUntil;
    }
  }

  void syncInputs() override {
    // Does nothing
  }

  // Controls:
private:
  bool paused = false;

public:
  bool isPaused() { return paused; }
  void pause() { paused = true; }
  void resume() { paused = false; }
  void togglePause() { paused = !paused; }
};
