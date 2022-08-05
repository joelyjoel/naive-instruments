#include "Add.h"

// FIXME: This causes a memory leak!
void operator+=(SignalInput<double> &signalInput,
                Signal<double> &additionalSignal) {
  Add *add = new Add();
  if (signalInput.hasPlug()) {
    add->a << signalInput.currentConnection();
  } else {
    add->a << signalInput.currentConstant();
  }
  add->b << additionalSignal;
  signalInput << add;
}
