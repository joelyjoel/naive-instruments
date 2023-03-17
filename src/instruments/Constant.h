#pragma once

#include "../core.h"
#include <iostream>

class Constant : public FrameStream<double> {
private:
  double value = 0;

public:
  Constant(double k) : value(k) {}
  void action() { writeFrame(value); }
};
