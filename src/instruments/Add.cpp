#include "Add.h"

// TODO: Refactor to use the + operator overloads
void operator+=(SignalInput<double> &signalInput,
                shared_ptr<Signal<double>> additionalSignal) {
  shared_ptr<Add> add = make_shared<Add>();
  if (signalInput.hasConnection()) {
    add->a << signalInput.typedConnection();
  } else {
    add->a << signalInput.currentConstant();
  }
  add->b << additionalSignal;
  signalInput << add;
}

shared_ptr<Signal<double>> operator+(shared_ptr<Signal<double>> a,
                                     shared_ptr<Signal<double>> b) {
  shared_ptr<Add> add = make_shared<Add>();
  add->a << a;
  add->b << b;
  return add;
}
