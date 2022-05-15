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
  LFO(double modulationFrequency = 1, double modulationDepth = 1,
      double mainValue = 0)
      : Patch(sum) {
    osc.frequency = modulationFrequency;
    modulation.a = osc;
    modulation.b = modulationDepth;
    sum.a = mainValue;
    sum.b = modulation;
  }

  Socket<double> &frequency = exposeSocket(osc.frequency);
  Socket<double> &depth = exposeSocket(modulation.b);
  Socket<double> &center = exposeSocket(sum.a);
};
