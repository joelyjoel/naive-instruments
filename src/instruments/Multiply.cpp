#include "Multiply.h"

// FIXME: This causes a memory leak!
void operator*=(SignalInput<double> &signalInput, Signal<double> &scale) {
  Multiply *multiply = new Multiply();
  if (signalInput.hasConnection()) {
    multiply->a << signalInput.connection();
  } else {
    multiply->a << signalInput.currentConstant();
  }
  multiply->b << scale;
  signalInput << multiply;
}

Signal<double> *operator*(Signal<double> &a, Signal<double> &b) {
  Multiply *m = new Multiply;
  m->a << a;
  m->b << b;
  return m;
}
