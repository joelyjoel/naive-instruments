#pragma once

#include "../core.h"

class Multiply : public Signal<double> {
public:
  SignalInput<double> &a = addSocket<double>();
  SignalInput<double> &b = addSocket<double>();

  double tick() { return a() * b(); }
};

/**
 * Mix an additional signal into a socket
 */
void operator*=(SignalInput<double> &socket, Signal<double> &additionalSignal);
