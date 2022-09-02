#include "Signal.h"

// --------------------------------------------------------------------------------
// class UntypedSignalInput
// --------------------------------------------------------------------------------

UntypedSignalInput::UntypedSignalInput(UntypedSignal *owner,
                                       const std::string &name)
    : owner(owner) {
  owner->inputs.push_back(this);
};

void UntypedSignalInput::connect(shared_ptr<Signal<double>> signal) {
  ;
  std::cerr << "No override for "
               "UntypedSignalInput::connect method\n";
  throw 1;
}

void UntypedSignalInput::setConstant(double k) {
  std::cerr
      << "No override for UntypedSignalInput::setConstant(double) method\n";
  throw 1;
}

UntypedSignal *untypedConnection = nullptr;

bool UntypedSignalInput::hasConnection() {
  return untypedConnection != nullptr;
}

void UntypedSignalInput::reset() {
  if (hasConnection())
    untypedConnection->reset();
}

void UntypedSignalInput::sync(int clock) {
  if (hasConnection())
    untypedConnection->sync(clock);
}

// --------------------------------------------------------------------------------
// class SignalInput
// --------------------------------------------------------------------------------
