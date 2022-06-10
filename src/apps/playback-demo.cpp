#include "../lib.h"
#include "portaudio.h"
#include <iostream>

int main() {
  std::cout << "Playing...\n";

  Sine signal;
  signal << 100;

  BufferedPlayback::play(signal);
}
