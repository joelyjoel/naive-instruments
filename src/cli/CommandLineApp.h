#pragma once

#include "../core.h"
#include "../file-io/WavWriter.h"
#include "../playback/BufferedPlayback.h"
#include "CommandLineArguments.h"
#include <iostream>

class CommandLineApp {
public:
  CommandLineArguments args;

public:
  CommandLineApp(int argc, char **argv) : args(argc, argv) {}
  CommandLineApp(MainArgs &args) : args(args) {}

  void output(MonoBuffer &buffer) {
    if (args.boolean("normalise"))
      buffer.normalise();
    if (outputPath().empty()) {
      BufferedPlayback::play(buffer);
    } else {
      WavWriter::write(outputPath(), buffer);
    }
  }

  void output(NaiveInstrument<double> &signal) {
    if (outputPath().empty())
      BufferedPlayback::play(signal);
    else
    // TODO: Handle case where -o is given
    {
      error("Not implemented saving multiple signals yet");
      throw TODO;
    }
  }

  void output(MonoBuffer *buffer) { output(*buffer); }

  const std::string outputPath() { return args.string("o", ""); }

  // TODO: getSample() for getting input samples

private:
  virtual void run() { std::cout << "Not implemented...\n"; }

protected:
  void error(const std::string &errMessage) {
    std::cerr << "Error: " << errMessage << "\n";
  }
};
