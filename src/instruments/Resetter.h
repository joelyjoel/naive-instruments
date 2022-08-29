#pragma once

#include "../core.h"

class Resetter : public Signal<double> {
public:
  SignalInput<double> input{this, "input"};
  SignalInput<bool> trigger{this, "trigger/bool"};

protected:
  void action() override {
    if (trigger())
      input.reset();
    out(input());
  }
};
