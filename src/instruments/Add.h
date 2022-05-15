#pragma once

#include "../core.h"
#include <iostream>
#include <string>

class Add : public NaiveInstrument<double> {
public:
  Socket<double> &a = addSocket<double>();
  Socket<double> &b = addSocket<double>();

  Add() : Add(0, 0) {}
  template <typename T, typename U> Add(T leftOperand = 0, U rightOperand = 0) {
    a = leftOperand;
    b = rightOperand;
  }
  double tick() { return a() + b(); }

  std::string label() { return "Add"; }
};
