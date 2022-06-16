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

public:
  static NaiveInstrument<double> *
  many(std::vector<NaiveInstrument<double> *> &inputs) {
    if (inputs.size() == 0)
      // TODO: Return silence
      throw TODO;
    else {
      NaiveInstrument *sum = inputs[0];
      for (int i = 1; i < inputs.size(); ++i) {
        Add *newAdd = new Add;
        newAdd->a << sum;
        newAdd->b << inputs[i];
        sum = newAdd;
      }
      return sum;
    }
  }
};
