#include "BufferedPlayback.h"
#include <iostream>
class InteractivePlayback {
  BufferedPlayback bufferedPlayback;

  InteractivePlayback(Signal<double> &input) : bufferedPlayback(input) {}

  void start(bool async = false) {
    std::cerr << "Starting interactive playback";
    bufferedPlayback.start();
  }

public:
  static void play(Signal<double> &signal) {
    InteractivePlayback playback(signal);
    playback.start(false);
  }

  static void play(MonoBuffer &audio) {
    // FIXME: Memory leak!
    Sampler *sampler = new Sampler(audio);
    play(*sampler);
  }
};
