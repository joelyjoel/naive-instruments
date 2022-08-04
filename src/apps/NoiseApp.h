#include "../lib.h"

class NoiseApp : public AudioCommand {
public:
  using AudioCommand::AudioCommand;

protected:
  void describeOptions() override { describeOutputOptions(); }

protected:
  void action() override {
    Noise noise;
    output(noise);
  }
};
