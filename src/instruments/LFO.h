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

  Socket<double> &frequency = exposeSocket(osc.frequency);
  Socket<double> &depth = exposeSocket(modulation.b);
  Socket<double> &center = exposeSocket(sum.a);
};
