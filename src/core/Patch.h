#pragma once

#include "Signal.h"
#include <string>

template <typename SignalFrame> class Patch : public Signal<SignalFrame> {
private:
  Signal<SignalFrame> &output;

public:
  Patch(Signal<SignalFrame> &output) : output(output) {}

  void action() {
    Signal<SignalFrame>::out(output.tickUntil(UntypedSignal::internalClock));
  }

protected:
  template <typename T> SignalInput<T> &exposeInput(SignalInput<T> &input) {
    Signal<SignalFrame>::inputs.push_back(&input);
    return input;
  }

  std::string label() { return "Patch"; }
};
