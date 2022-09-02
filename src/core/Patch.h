#pragma once

#include "Signal.h"
#include <string>

template <typename SignalFrame> class Patch : public Signal<SignalFrame> {
private:
  /**
   * Pointer to the signal nominated as this patch's output signal.
   */
  shared_ptr<Signal<SignalFrame>> output;

public:
  /* Patch(shared_ptr<Signal<SignalFrame>> output) { exposeOutput(output); } */

public:
  void action() {
    output->sync(this->internalClock);
    this->out((*output)());
  }

protected:
  template <typename T> SignalInput<T> &exposeInput(SignalInput<T> &input) {
    Signal<SignalFrame>::inputs.push_back(&input);
    return input;
  }

protected:
  void exposeOutput(shared_ptr<Signal<SignalFrame>> outputSignal) {
    if (!outputSignal) {
      std::cerr << "output pointer is null in " << label() << "\n";
      throw 1;
    }
    output = outputSignal;
  }

  std::string label() { return "Patch"; }
};
