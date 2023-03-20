#include "../core.h"

class MonoToStereo : public FrameStream<StereoFrame> {
public:
  SignalInput<double> input{this, "input"};

protected:
  void action() override {
    output->left = input.readFrame();
    output->right = input.readFrame();
  }
};

class MixdownToMono : public FrameStream<double> {
  SignalInput<StereoFrame> input{this, "input"};

protected:
  void action() override {
    *output = .5 * (input.readFrame().left + input.readFrame().right);
  }
};
