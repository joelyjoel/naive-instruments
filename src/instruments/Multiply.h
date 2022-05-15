#pragma once

#include "../core.h"

class Multiply : public NaiveInstrument<double> {
public:
  Socket<double> &a = addSocket<double>();
  Socket<double> &b = addSocket<double>();

  template <typename T, typename U> Multiply(T leftOperand, U rightOperand) {
    a = leftOperand;
    b = rightOperand;
  }
  double tick() { return a() * b(); }
};
