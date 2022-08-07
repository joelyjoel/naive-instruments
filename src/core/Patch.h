#pragma once

#include "Signal.h"
#include <string>

template <typename SignalFrame> class Patch : public Signal<SignalFrame> {
private:
  Signal<SignalFrame> &output;

public:
  Patch(Signal<SignalFrame> &output) : output(output) {}

  void action() {
    output.sync(this->internalClock);
    this->out(output());
  }

protected:
  template <typename T> SignalInput<T> &exposeInput(SignalInput<T> &input) {
    Signal<SignalFrame>::inputs.push_back(&input);
    return input;
  }

  std::string label() { return "Patch"; }
};
