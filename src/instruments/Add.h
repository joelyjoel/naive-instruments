#pragma once

#include "../core.h"
#include "Constant.h"
#include <iostream>
#include <string>

class Add : public Signal<double> {
public:
  SignalInput<double> &a = addInput<double>("a");
  SignalInput<double> &b = addInput<double>("b");

  Add() {}

  void action() { out(a() + b()); }

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
 * Mix an additional signal into an input
 */
void operator+=(SignalInput<double> &signalInput,
                Signal<double> &additionalSignal);

Signal<double> *operator+(Signal<double> &a, Signal<double> &b);
