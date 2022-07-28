#include "../lib.h"

class FilterApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() override {
    MonoBuffer *input = mainInputAsBuffer();

    Sampler sampler(*input);
    ButterworthFilter filter;

    filter.kind = getFilterKind();

    filter.input << sampler;

    if (args.exists("frequency")) {
      auto frequency = args.signal("frequency");
      filter.frequency << frequency;
      output(filter);
    } else if (args.exists("pitch")) {
      PitchConverter pitchConverter;
      auto pitch = args.signal("pitch");
      filter.frequency << pitchConverter << *pitch;
      output(filter);
    } else {
      std::cerr << "No --frequency or --pitch specified\n";
      throw 1;
    }
  }

  ButterworthFilter::FilterKind getFilterKind() {
    if (args.flag("hp"))
      return ButterworthFilter::HighPass;
    else if (args.flag("bp"))
      return ButterworthFilter::BandPass;
    else if (args.flag("br"))
      return ButterworthFilter::BandReduce;
    else if (args.flag("lp"))
      return ButterworthFilter::LowPass;
    else
      return ButterworthFilter::LowPass;
  }
};
