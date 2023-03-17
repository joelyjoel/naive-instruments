#pragma once

#include "../core.h"

class Resetter : public FrameStream<double> {
public:
  SignalInput<double> input{this, "input"};
  SignalInput<bool> trigger{this, "trigger/bool"};

  static shared_ptr<Resetter> create() { return make_shared<Resetter>(); }

protected:
  void action() override {
    if (trigger())
      input.reset();
    out(input());
  }
};
