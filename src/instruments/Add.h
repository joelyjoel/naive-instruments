#pragma once

#include "../core.h"
#include "Constant.h"
#include <iostream>
#include <string>

class Add : public Signal<double> {
public:
  Socket<double> &a = addSocket<double>();
  Socket<double> &b = addSocket<double>();

  Add() {}

  double tick() { return a() + b(); }

  std::string label() { return "Add"; }

public:
  static Signal<double> *many(std::vector<Signal<double> *> &inputs) {
    if (inputs.size() == 0)
      return new Constant(0);
    else {
      Signal *sum = inputs[0];
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

/**
 * Mix an additional signal into a socket
 */
void operator+=(Socket<double> &socket, Signal<double> &additionalSignal);
