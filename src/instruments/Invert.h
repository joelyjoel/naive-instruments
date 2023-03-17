#include "../core.h"

class Invert : public FrameStream<double> {
public:
  SignalInput<double> input{this, "input"};

protected:
  void action() override { out(-input()); }
};
