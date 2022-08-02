#pragma once

#include "../core.h"

class Multiply : public NaiveInstrument<double> {
public:
  Socket<double> &a = addSocket<double>();
  Socket<double> &b = addSocket<double>();

  double tick() { return a() * b(); }
};

/**
 * Mix an additional signal into a socket
 */
void operator*=(Socket<double> &socket,
                NaiveInstrument<double> &additionalSignal);
