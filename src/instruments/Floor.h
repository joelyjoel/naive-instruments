#pragma once

#include "../core.h"
#include <cmath>

class Floor : public FrameStream<double> {
public:
  SignalInput<double> input{this, "input"};

  void action() { out(floor(input())); }
};
