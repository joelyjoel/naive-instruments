#include "Multiply.h"

// FIXME: This causes a memory leak!
void operator*=(FrameStreamConsumer<double> &signalInput,
                shared_ptr<FrameStream<double>> scale) {
  shared_ptr<Multiply> multiply = make_shared<Multiply>();
  multiply->a << signalInput.typedConnection();
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
