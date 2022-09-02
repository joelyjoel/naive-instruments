#pragma once

#include "../core.h"
#include "Add.h"
#include "Multiply.h"
#include "Osc.h"

class LFO : public Patch<double> {
private:
  // TODO: Make the waveform customisable
  shared_ptr<Sine> osc = make_shared<Sine>();
  shared_ptr<Multiply> modulation = make_shared<Multiply>();
  shared_ptr<Add> sum = make_shared<Add>();

public:
  LFO() {
    modulation->a << osc;
    sum->b << modulation;
    exposeOutput(sum);
  }

  std::string label() { return "LFO"; }

  SignalInput<double> &frequency = exposeInput(osc->frequency);
  SignalInput<double> &depth = exposeInput(modulation->b);
  SignalInput<double> &center = exposeInput(sum->a);
};
