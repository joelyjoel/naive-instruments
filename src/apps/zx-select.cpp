#include "../analysis/WaveformBufferer.h"
#include "../cli/CommandLineArguments.h"
#include "../lib.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  CommandLineArguments args(argc, argv);
  const std::string &inputFilePath = args[0];
  const std::string &outputPath = args["o"];
  bool normalize = args.boolean("normalize");
  std::cerr << "Normalize: " << normalize << "\n";

  Sampler sampler(inputFilePath);
  WaveformBufferer bufferer;
  bufferer.minNumberOfFrames = args.integer("min-frames", 100);

  bufferer << sampler;

  auto indexToSelect = args.requireInt("index");

  MonoBuffer *waveform = bufferer[indexToSelect];

  if (normalize)
    waveform->normalise();

  WavWriter::write(outputPath, *waveform);
  std::cout << outputPath;
}
