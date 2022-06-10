// Play a tone and never stop!

#include <iostream>
int main(int argc, char **argv) {
  std::cout << "Use ctrl-c to stop the tone!\n";

  BufferedPlayback playback;

  Sine osc;
  osc << 440;

  playback.topUpBuffer(osc);
}
