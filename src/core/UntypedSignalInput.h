#include "Signal.h"

class UntypedSignalInput {
protected:
  UntypedSignal *owner;

public:
  UntypedSignalInput(UntypedSignal *owner) : owner(owner){};

  virtual void connect(Signal<double> *signal) {
    std::cerr << "No override for "
                 "AbstractSocket::connect(Signal<double>*) method\n";
    throw 1;
  }

public:
  virtual void setConstant(double k) {
    std::cerr << "No override for AbstractSocket::setConstant(double) method\n";
    throw 1;
  }

protected:
  UntypedSignal *untypedConnection = nullptr;

public:
  bool hasPlug() { return untypedConnection != nullptr; }
};
