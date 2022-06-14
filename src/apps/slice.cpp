#include "../lib.h"
#include <iostream>

// TODO: Probably rename as something like `sample`
// TODO: Refactor as class CommandLineSample (or similar)
int main(int argc, char **argv) {
  CommandLineArguments args(argc, argv);

  const auto filename = args[0];
  auto buffer = WavReader::readMonoFile(filename);

  // TODO: support time units: s, samp, zx, onset etc
  const float from = args.number("from", 0);
  const float to = args.number("to", buffer->duration());

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

  // TODO: Refactor as CommandLineApp .output(buffer)
  const std::string outputPath = args.string("o", "");
  if (args.boolean("normalise"))
    sliced->normalise();
  if (outputPath.empty()) {
    BufferedPlayback::play(*sliced);
  } else {
    WavWriter::write(outputPath, *sliced);
  }
}
