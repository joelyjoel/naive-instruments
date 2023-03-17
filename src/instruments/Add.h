#pragma once

#include "../core.h"
#include "Constant.h"
#include <iostream>
#include <string>

class Add : public FrameStream<double> {
public:
  SignalInput<double> a{this, "a"};
  SignalInput<double> b{this, "b"};

  Add() {}

  void action() { writeFrame(a() + b()); }

  std::string label() { return "Add"; }

public:
  static shared_ptr<FrameStream<double>>
  many(std::vector<shared_ptr<FrameStream<double>>> &inputs) {
    if (inputs.size() == 0)
      return std::make_shared<Constant>(0);
    else {
      shared_ptr<FrameStream<double>> sum = inputs[0];
      for (int i = 1; i < inputs.size(); ++i) {
        shared_ptr<Add> newAdd = std::make_shared<Add>();
        newAdd->a << sum;
        newAdd->b << inputs[i];
        sum = newAdd;
      }
      return sum;
    }
  }

  friend void operator+=(SignalInput<double> &signalInput,
                         shared_ptr<FrameStream<double>>);
  ;
};

/**
 * Mix an additional signal into an input.
 */
void operator+=(SignalInput<double> &signalInput,
                shared_ptr<FrameStream<double>> &additionalSignal);

shared_ptr<FrameStream<double>> operator+(shared_ptr<FrameStream<double>> a,
                                          shared_ptr<FrameStream<double>> b);
