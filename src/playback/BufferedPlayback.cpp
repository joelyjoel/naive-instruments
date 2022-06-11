#include "BufferedPlayback.h"
#include "portaudio.h"
#include <iostream>

static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags, void *userData) {

  BufferedPlayback *bufferedPlayback = (BufferedPlayback *)userData;

  float *out = (float *)outputBuffer;
  for (unsigned int i = 0; i < framesPerBuffer; ++i)
    out[i] = bufferedPlayback->shift();

  (void)inputBuffer; /* Prevent unused variable warning. */

  double rms = 0;
  for (int i = 0; i < framesPerBuffer; ++i)
    rms += out[i] * out[i];
  rms = sqrt(rms / framesPerBuffer);

  return 0;
}

void BufferedPlayback::start() {

  // Initialise Portaudio
  std::cout << "Initialising port audio\n";
  err = Pa_Initialize();
  assertNotError();

  std::cout << "Creating PA stream\n";
  int numberOfInputChannels = 0;
  int numberOfOutputChannels = 1;
  int sampleRate = 44100;
  int framesPerBuffer = 256;
  err = Pa_OpenDefaultStream(&stream, numberOfInputChannels,
                             numberOfOutputChannels, paFloat32, sampleRate,
                             framesPerBuffer, audioCallback, this);
  assertNotError();

  err = Pa_StartStream(stream);
  assertNotError();
}
