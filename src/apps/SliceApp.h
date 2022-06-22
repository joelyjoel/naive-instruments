#include "../lib.h"

class SliceApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() {
    const auto filename = args[0];
    auto buffer = WavReader::readMonoFile(filename);

    const float from = args.time("from", "0s");
    // TODO: not 100s
    const float to = args.time("to", "100s");

    MonoBuffer *sliced = buffer->slice(from, to);

    // TODO: refactor using move semantics
    const float numberOfRepetitions = args.number("repeat", 1);
    if (numberOfRepetitions != 1) {
      std::cerr << "repeating\n";
      auto repeated = sliced->repeat(numberOfRepetitions);
      delete sliced;
      sliced = repeated;
      // TODO: Configurable crossfades
    }

    const float fadeIn = args.number("fadeIn", 0.005);
    sliced->fadeIn(fadeIn);

    const float fadeOut = args.number("fadeOut", 0.005);
    sliced->fadeOut(fadeOut);

    const float fade = args.number("fade", 0);
    sliced->fadeBoth(fade);

    // TODO: --loopUntil duration (overrides repeat)
    // TODO: --after - adding silence before the sample

    output(sliced);
  }
};
