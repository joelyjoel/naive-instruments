#pragma once
#include "NaiveInstrument.h"
#include "Socket.h"

class Add : public NaiveInstrument<double> {
  Socket<double> &a = addSocket<double>();
  Socket<double> &b = addSocket<double>();

public:
  template <typename T, typename U> Add(T leftOperand, U rightOperand) {
    a = leftOperand;
    b = rightOperand;
  }
  double tick() { return a() + b(); }
};
