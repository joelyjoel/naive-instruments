#pragma once

#include "../core.h"
#include "Add.h"
#include "Multiply.h"
#include "Osc.h"

class LFO : public Patch<double> {
private:
  Sine osc;
  Multiply modulation;
  Add sum;

public:
  LFO() : Patch(sum) {
    modulation.a << osc;
    sum.b << modulation;
  }

  SignalInput<double> &frequency = exposeSocket(osc.frequency);
  SignalInput<double> &depth = exposeSocket(modulation.b);
  SignalInput<double> &center = exposeSocket(sum.a);
};
