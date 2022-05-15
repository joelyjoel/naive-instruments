#pragma once

#include "../core.h"
#include <iostream>
#include <string>

class Add : public NaiveInstrument<double> {
public:
  Socket<double> &a = addSocket<double>();
  Socket<double> &b = addSocket<double>();

  Add() {}

  double tick() { return a() + b(); }

  std::string label() { return "Add"; }
};
