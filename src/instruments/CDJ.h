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

      // TODO: This bit could be branchless using modulo?
      playhead += rate;
      if (looping && playhead > loopEnd)
        playhead -= loopEnd - loopStart;
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

  // Play/pause
private:
  bool paused = false;

public:
  bool isPaused() { return paused; }
  void pause() { paused = true; }
  void resume() { paused = false; }
  void togglePause() { paused = !paused; }

public:
  void restart() { playhead = 0; }

  void skipForward(float seconds) { playhead += seconds * sampleRate; }

  // Playback rate
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
    std::string icon;
    if (detune == 0)
      icon = "\u266e";
    else if (detune > 0)
      icon = "\u266f";
    else if (detune < 0) {
      detune = -detune;
      icon = "\u266d";
    }

    return icon + std::to_string(detune);
  }

  // Looping
private:
  bool looping = false;
  float loopStart = 0;
  float loopEnd;

public:
  void setLoop(float start = 0, float end = 0) {
    if (end == 0)
      end = playhead;
    loopStart = start;
    loopEnd = end;
    looping = true;
  }
  bool isLooping() { return looping; }
  void punchInLoop() {
    loopStart = playhead;
    loopPunchState = 1;
  }
  void punchOutLoop() {
    loopEnd = playhead;
    looping = true;
    loopPunchState = 2;
  }
  void breakOutOfLoop() { looping = false; }
  char loopPunchState = 0;
  void punchLoop() {
    switch (loopPunchState) {
    case 0:
      punchInLoop();
      break;
    case 1:
      punchOutLoop();
      break;
    case 2:
      punchInLoop();
      breakOutOfLoop();
      break;
    default:
      std::cerr << "oh no!\n";
      break;
    }
  }

  std::string describeLoopState() {
    if (looping)
      return "\uf955 LOOPING";
    else if (loopPunchState == 1)
      return "\uf956 Punching into loop";
    else
      return "\uf956";
  }

  // TODO: listen to Connie converse
  float timeElapsed() { return playhead / sampleRate; }

  std::string describeTimeElapsed() {
    return std::to_string(int(timeElapsed() / 60)) + ":" +
           std::to_string(fmod(timeElapsed(), 60));
  }
};
