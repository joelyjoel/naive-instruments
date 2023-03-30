#pragma once

#include "../core.h"
#include "Add.h"
#include "Multiply.h"
#include "Osc.h"

class LFO : public Patch<double> {
private:
  // TODO: Make the waveform customisable
  shared_ptr<Osc> osc = Osc::create_sine();
  shared_ptr<Multiply> modulation = Multiply::create();
  shared_ptr<Add> sum = make_shared<Add>();

public:
  LFO() {
    modulation->a << osc;
    sum->b << modulation;
    exposeOutput(sum);
  }

  std::string label() { return "LFO"; }

  FrameStreamConsumer<double> &frequency = exposeInput(osc->frequency);
  FrameStreamConsumer<double> &depth = exposeInput(modulation->b);
  FrameStreamConsumer<double> &center = exposeInput(sum->a);
};
