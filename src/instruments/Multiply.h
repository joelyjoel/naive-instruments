#pragma once

#include "../core.h"

class Multiply : public FrameStream<double> {
public:
  SignalInput<double> a{this, "a"};
  SignalInput<double> b{this, "a"};

protected:
  void action() override { out(a() * b()); }

public:
  std::string label() override { return "Multiply"; }

  static shared_ptr<Multiply> create() { return make_shared<Multiply>(); }
};

/**
 * Mix an additional signal into a input
 */
void operator*=(SignalInput<double> &signalInput,
                shared_ptr<FrameStream<double>> additionalSignal);

shared_ptr<FrameStream<double>> operator*(shared_ptr<FrameStream<double>> a,
                                          shared_ptr<FrameStream<double>> b);
