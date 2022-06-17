#pragma once

#include <exception>
#include <iostream>
#include <portaudio.h>

#include "../core.h"

#include "../instruments/Sampler.h"
#include "./CircularBuffer.h"

static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags, void *userData);

class BufferedPlayback {
private:
  PaStream *stream;
  PaError err;

public:
  BufferedPlayback() : buffer(1024) {}
  CircularBuffer<double> buffer;
  double shift() { return buffer.shift(); }
  void push(double y) { buffer.push(y); }

  void assertNotError() {
    if (err != paNoError) {
      std::cerr << "Port audio error:" << Pa_GetErrorText(err) << "\n";
      throw 1;
    }
  }

  void start();

  void stop() {
    std::cout << "Stopping stream\n";
    err = Pa_StopStream(stream);
    assertNotError();

    std::cout << "Terminating port audio\n";
    err = Pa_Terminate();
    assertNotError();
  }

  void topUpBuffer(NaiveInstrument<double> &signal) {
    while (buffer.hasFreeSpace()) {
      buffer.push(signal.next());
    }
  }

  double idealTopUpInterval() {
    return float(buffer.size()) / float(sampleRate);
  }

  static void play(NaiveInstrument<double> &signal) {
    // TODO: Create a seperate loader thread
    BufferedPlayback playback;
    playback.topUpBuffer(signal);
    playback.start();
    while (true) {
      playback.topUpBuffer(signal);
      Pa_Sleep(playback.idealTopUpInterval() * 1000 * .25);
    }
  }

  static void play(MonoBuffer &audio) {
    Sampler sampler(audio);
    play(sampler);
  }
};
