#pragma once

#include "../core.h"

class Multiply : public Signal<double> {
public:
  SignalInput<double> a{this, "a"};
  SignalInput<double> b{this, "a"};

  void action() override { out(a() * b()); }
  std::string label() override { return "Multiply"; }
};

/**
 * Mix an additional signal into a input
 */
void operator*=(SignalInput<double> &signalInput,
                Signal<double> &additionalSignal);

Signal<double> *operator*(Signal<double> &a, Signal<double> &b);
