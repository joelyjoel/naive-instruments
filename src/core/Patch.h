#pragma once

#include "Signal.h"
#include <string>

template <typename SignalFrame> class Patch : public Signal<SignalFrame> {
private:
  Signal<SignalFrame> &output;

public:
  Patch(Signal<SignalFrame> &output) : output(output) {}

  void action() { Signal<SignalFrame>::out(output[this->internalClock]); }

protected:
  template <typename T> SignalInput<T> &exposeInput(SignalInput<T> &input) {
    this->addInput(&input);
    return input;
  }

  std::string label() { return "Patch"; }
};
