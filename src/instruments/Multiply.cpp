#include "Multiply.h"

// FIXME: This causes a memory leak!
void operator*=(SignalInput<double> &signalInput,
                shared_ptr<FrameStream<double>> scale) {
  shared_ptr<Multiply> multiply = make_shared<Multiply>();
  if (signalInput.hasConnection()) {
    multiply->a << signalInput.typedConnection();
  } else {
    multiply->a << signalInput.currentConstant();
  }
  multiply->b << scale;
  signalInput << multiply;
}

shared_ptr<FrameStream<double>> operator*(shared_ptr<FrameStream<double>> a,
                                          shared_ptr<FrameStream<double>> b) {
  shared_ptr<Multiply> m = make_shared<Multiply>();
  m->a << a;
  m->b << b;
  return m;
}
