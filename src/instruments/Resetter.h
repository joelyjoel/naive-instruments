#include "../core.h"

class Resetter : public Signal<double> {
public:
  SignalInput<double> &input = addInput<double>();
  SignalInput<bool> &trigger = addInput<bool>();

protected:
  void action() override {
    if (trigger())
      input.reset();
    out(input());
  }
};
