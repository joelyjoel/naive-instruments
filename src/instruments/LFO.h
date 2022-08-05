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

  SignalInput<double> &frequency = exposeInput(osc.frequency);
  SignalInput<double> &depth = exposeInput(modulation.b);
  SignalInput<double> &center = exposeInput(sum.a);
};
