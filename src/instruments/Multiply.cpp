#include "Multiply.h"

// FIXME: This causes a memory leak!
void operator*=(Socket<double> &socket, NaiveInstrument<double> &scale) {
  Multiply *multiply = new Multiply();
  if (socket.hasPlug()) {
    multiply->a << socket.currentConnection();
  } else {
    multiply->a << socket.currentConstant();
  }
  multiply->b << scale;
  socket << multiply;
}
