#include "../lib.h"

// TODO: Probably rename as something like `sample`
// TODO: Refactor as class CommandLineSample (or similar)
int main(int argc, char **argv) {
  CommandLineArguments args(argc, argv);

  const auto filename = args[0];
  auto buffer = WavReader::readMonoFile(filename);

  const float from = args.number("from", 0);
  const float to = args.number("to", buffer->duration());

  MonoBuffer *sliced = buffer->slice(from, to);

  // TODO: --fade --fadeIn and --fadeOut
  // TODO: --repeat for looping the sample
  // TODO: --loopUntil duration (overrides repeat)
  // TODO:
  // TODO: --delay - adding silence before the sample

  // TODO: Refactor as CommandLineApp .output(buffer)
  const std::string outputPath = args.string("o", "");
  // TODO: --normalise : normalise the output
  if (outputPath.empty()) {
    BufferedPlayback::play(*sliced);
  } else {
    WavWriter::write(outputPath, *sliced);
  }
}
