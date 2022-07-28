#include "../lib.h"

class RandomEnvelopeApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

  BreakpointEnvelope env;

  float min = args.number("min", 9);
  float max = args.number("max", 108);
  float randomValue() { return random(min, max); }

  float minSectionDuration = args.number("min-section-duration", 0);
  float maxSectionDuration = args.number("max-section-duration", .8);
  float randomSectionDuration() {
    return random(minSectionDuration, maxSectionDuration);
  }

  float chanceOfSkip = args.number("chance-of-skip", .5);

  float duration = args.number("duration", 1);

public:
  void run() override {

    srand(time(NULL));

    env.addSection(randomValue(), randomValue(), randomSectionDuration());
    do {
      if (random.chance(chanceOfSkip))
        env.addSection(randomValue(), randomSectionDuration());
      else
        env.addSection(randomValue(), randomValue(), randomSectionDuration());
    } while (env.duration() < duration);

    if (random.chance(1 - chanceOfSkip))
      env.closeTheLoop(randomSectionDuration());

    /* for (auto section : env.sections) { */
    /*   section.duration /= (section.startValue + section.endValue) / 200; */
    /* } */

    std::cout << env << "\n";
  }
};
