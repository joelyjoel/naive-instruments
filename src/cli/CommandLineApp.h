#pragma once

#include "../core.h"
#include "../file-io/WavWriter.h"
#include "../playback/BufferedPlayback.h"
#include "CommandLineArguments.h"

class CommandLineApp {
public:
  CommandLineArguments args;

public:
  CommandLineApp(int argc, char **argv) : args(argc, argv) {}

  void output(MonoBuffer &buffer) {
    const std::string outputPath = args.string("o", "");
    if (args.boolean("normalise"))
      buffer.normalise();
    if (outputPath.empty()) {
      BufferedPlayback::play(buffer);
    } else {
      WavWriter::write(outputPath, buffer);
    }
  }

  void output(MonoBuffer *buffer) { output(*buffer); }
};
