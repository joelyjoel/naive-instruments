#include "Add.h"

// FIXME: This causes a memory leak!
void operator+=(SignalInput<double> &signalInput,
                Signal<double> &additionalSignal) {
  Add *add = new Add();
  if (signalInput.hasConnection()) {
    add->a << signalInput.connection();
  } else {
    add->a << signalInput.currentConstant();
  }
  add->b << additionalSignal;
  signalInput << add;
}

Signal<double> *operator+(Signal<double> &a, Signal<double> &b) {
  Add *add = new Add;
  add->a << a;
  add->b << b;
  return add;
}
