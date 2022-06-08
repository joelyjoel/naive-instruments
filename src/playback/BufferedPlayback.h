#include <exception>
#include <iostream>
#include <portaudio.h>

#include "./CircularBuffer.h"

static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags, void *userData);

class BufferedPlayback {
public:
  BufferedPlayback() : buffer(44100) {}
  CircularBuffer<double> buffer;
  double shift() { return buffer.shift(); }
  void push(double y) { buffer.push(y); }

  void assertNotError(PaError err) {
    if (err != paNoError) {
      std::cerr << "Port audio error:" << Pa_GetErrorText(err) << "\n";
      throw 1;
    } else {
      std::cerr << "No error\n";
    }
  }

  void start();
};
