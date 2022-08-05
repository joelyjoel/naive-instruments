#pragma once

#include "../core.h"

class Multiply : public Signal<double> {
public:
  SignalInput<double> &a = addInput<double>();
  SignalInput<double> &b = addInput<double>();

  void tick() { out(a() * b()); }
};

/**
 * Mix an additional signal into a socket
 */
void operator*=(SignalInput<double> &socket, Signal<double> &additionalSignal);
