#include "../lib.h"
#include "portaudio.h"
#include <iostream>

int main() {
  std::cout << "Playing...\n";

  Sine signal;
  LFO lfo;
  lfo.center << 100;
  lfo.depth << 40;
  lfo.frequency << .1;
  signal << lfo;

  BufferedPlayback::play(signal);
}
