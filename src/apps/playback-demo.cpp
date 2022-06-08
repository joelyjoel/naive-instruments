#include "../lib.h"
#include <iostream>

int main() {
  std::cout << "Playing...\n";

  BufferedPlayback playback;

  for (int i = 0; i < 44100; ++i)
    playback.push(float(i % 441) / 441.0);

  playback.start();
}
