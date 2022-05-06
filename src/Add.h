#pragma once
#include "NaiveInstrument.h"
#include "Socket.h"

class Add : public NaiveInstrument<double> {
  Socket<double> a;
  Socket<double> b;

public:
  template <typename T, typename U>
  Add(T leftOperand, U rightOperand) : a(this), b(this) {
    a = leftOperand;
    b = rightOperand;
  }
  double tick() { return a() + b(); }
};
