#pragma once

#include "../core.h"
#include <iostream>
#include <string>

class CDJ : public Signal<double> {

public:
  SignalInput<double> input{this, "input"};
  float playhead = 0.0;

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
      out(internalBuffer[int(playhead) % bufferSize]);
      playhead += rate;
    }
  }

  void bufferMore() {
    while (bufferedUntil < playhead + lookAhead) {
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

private:
  float rate = 1.0;

public:
  float playbackRate() { return rate; }
  void semitoneFaster(float numberOfSemitones = 1.0) {
    rate *= pow(2.0, numberOfSemitones / 12.0);
  }
  void semitoneSlower(float numberOfSemitones = 1.0) {
    rate /= pow(2.0, numberOfSemitones / 12.0);
  }

  float detuneInSemitones() {
    // rate = 2 ^ (n/12)
    // ln(rate) = (n/12) * ln(2)
    // n/12 = ln(rate)/ln(2)
    // n = 12 * ln(rate) / ln(2)
    return 12 * log(rate) / log(2);
  }

  std::string describeDetune() {
    float detune = detuneInSemitones();

    return std::to_string(detune);
  }
};
