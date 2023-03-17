#include "Signal.h"

// --------------------------------------------------------------------------------
// class UntypedSignalInput
// --------------------------------------------------------------------------------

UntypedSignalInput::UntypedSignalInput(AbstractFrameStream *owner,
                                       const std::string &name,
                                       bool keepSyncedToOwner)
    : owner(owner), keepSyncedToOwner(keepSyncedToOwner), name(name) {
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

void UntypedSignalInput::checkConnection() {
  if (untypedConnection == nullptr) {
    std::cerr << label() << " has no connection\n";
    throw 1;
  }
}

void UntypedSignalInput::reset() {
  checkConnection();
  untypedConnection->reset();
}

void UntypedSignalInput::sync(int clock) {
  checkConnection();
  untypedConnection->sync(clock);
}

void UntypedSignalInput::syncToOwner() {
  checkConnection();
  if (keepSyncedToOwner)
    untypedConnection->sync(owner->internalClock);
}

std::string UntypedSignalInput::label() {
  return owner->label() + "." + this->name;
}

// --------------------------------------------------------------------------------
// class SignalInput
// --------------------------------------------------------------------------------

#include "../instruments/Constant.h"

template <typename frame> void SignalInput<frame>::setConstant(frame k) {
  connect(make_shared<Constant<frame>>(k));
}

void AVOID_LINKING_ERRORS() {
  SignalInput<double> compileItForDoubles(nullptr, "hello", true);
  SignalInput<bool> compileItForBools(nullptr, "hello", true);
}
