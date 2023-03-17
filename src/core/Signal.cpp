#include "Signal.h"

// --------------------------------------------------------------------------------
// class UntypedSignalInput
// --------------------------------------------------------------------------------

UntypedSignalInput::UntypedSignalInput(AbstractFrameStream *owner,
                                       const std::string &name,
                                       bool keepSyncedToOwner)
    : owner(owner), keepSyncedToOwner(keepSyncedToOwner) {
  owner->inputs.push_back(this);
};

void UntypedSignalInput::connect(shared_ptr<FrameStream<double>> signal) {
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

AbstractFrameStream *untypedConnection = nullptr;

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

void UntypedSignalInput::syncToOwner() {
  if (hasConnection() && keepSyncedToOwner)
    untypedConnection->sync(owner->internalClock);
}

// --------------------------------------------------------------------------------
// class SignalInput
// --------------------------------------------------------------------------------
