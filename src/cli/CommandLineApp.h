#pragma once

#include "../core.h"
#include "../file-io/WavWriter.h"
#include "../file-io/piping.h"
#include "../file-io/record.h"
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

    if (stdoutIsAPipe()) {
      std::cerr << "Piping to stdout\n";
      WavWriter::write(std::cout, buffer);
    } else if (outputPath().empty()) {
      BufferedPlayback::play(buffer);
    } else {
      WavWriter::write(outputPath(), buffer);
    }
  }

  MonoBuffer *mainInputAsBuffer() {
    if (args.exists("input")) {
      const auto filename = args["input"];
      return WavReader::readMonoFile(filename);
    } else if (stdinIsAPipe()) {
      return WavReader::readStream(std::cin);
    } else {
      // TODO: implement some kind of array shifting with positional arguments
      const auto filename = args[0];
      return WavReader::readMonoFile(filename);
    }
  }

  float duration() {
    const auto durationStr = args.require("duration");
    try {
      return *Parse::interval(durationStr);
    } catch (...) {
      std::cerr << "Couldn't parse --duration option\n";
      throw 1;
    }
  }

  void output(FrameStream<double> &signal) {
    auto &path = outputPath();
    if (stdoutIsAPipe()) {
      std::cerr << "Piping to stdout\n";
      record(std::cout, signal, duration());
    } else if (path.empty())
      BufferedPlayback::play(signal);
    else {
      record(path, signal, duration());
      std::cout << path << "\n";
    }
  }

  void output(MonoBuffer *buffer) { output(*buffer); }

  const std::string outputPath() { return args.string("o", ""); }

  // TODO: getSample() for getting input samples

private:
  virtual void run() { std::cout << "Not implemented...\n"; }

public:
  void operator()() { run(); }

protected:
  void error(const std::string &errMessage) {
    std::cerr << "Error: " << errMessage << "\n";
  }
};
