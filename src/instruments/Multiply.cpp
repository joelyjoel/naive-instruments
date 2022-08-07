#include "Multiply.h"

// FIXME: This causes a memory leak!
void operator*=(SignalInput<double> &signalInput, Signal<double> &scale) {
  Multiply *multiply = new Multiply();
  if (signalInput.hasConnection()) {
    multiply->a << signalInput.currentConnection();
  } else {
    multiply->a << signalInput.currentConstant();
  }
  multiply->b << scale;
  signalInput << multiply;
}
