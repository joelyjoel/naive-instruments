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
