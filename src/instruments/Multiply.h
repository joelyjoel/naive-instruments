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
                shared_ptr<Signal<double>> additionalSignal);

shared_ptr<Signal<double>> operator*(shared_ptr<Signal<double>> a,
                                     shared_ptr<Signal<double>> b);
