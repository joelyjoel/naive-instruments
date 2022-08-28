#pragma once

#include "../core.h"
#include <cmath>

class Floor : public Signal<double> {
public:
  SignalInput<double> &input = addInput<double>("input");

  void action() { out(floor(input())); }
};
