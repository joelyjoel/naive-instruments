#pragma once

#include "../core.h"

class Resetter : public Signal<double> {
public:
  SignalInput<double> &input = addInput<double>("input");
  SignalInput<bool> &trigger = addInput<bool>("trigger/bool");

protected:
  void action() override {
    if (trigger())
      input.reset();
    out(input());
  }
};
