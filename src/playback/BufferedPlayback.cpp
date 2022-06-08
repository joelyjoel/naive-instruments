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

  return 0;
}

void BufferedPlayback::start() {
  PaError err;

  // Initialise Portaudio
  std::cout << "Initialising port audio\n";
  err = Pa_Initialize();
  assertNotError(err);

  std::cout << "Creating PA stream\n";
  PaStream *stream;
  int numberOfInputChannels = 0;
  int numberOfOutputChannels = 1;
  int sampleRate = 44100;
  int framesPerBuffer = 2048;
  err = Pa_OpenDefaultStream(&stream, numberOfInputChannels,
                             numberOfOutputChannels, paFloat32, sampleRate,
                             framesPerBuffer, audioCallback, this);
  assertNotError(err);

  err = Pa_StartStream(stream);
  assertNotError(err);

  // TODO: Remove this
  std::cout << "Sleeping\n";
  Pa_Sleep(5000);
  std::cout << "Done!\n";

  std::cout << "Stopping stream\n";
  err = Pa_StopStream(stream);
  assertNotError(err);

  std::cout << "Terminating port audio\n";
  err = Pa_Terminate();
  assertNotError(err);

  std::cout << "All seems to have gone well!\n";
}
