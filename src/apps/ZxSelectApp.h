#include "../lib.h"

class ZxSelectApp : public CommandLineApp {
public:
  using CommandLineApp::CommandLineApp;

  void run() override {
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

    output(waveform);
  }
};
