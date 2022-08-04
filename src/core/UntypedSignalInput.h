#include "Signal.h"

class UntypedSignalInput {
protected:
  UntypedSignal *owner;

public:
  UntypedSignalInput(UntypedSignal *owner) : owner(owner){};

  virtual void connect(Signal<double> *signal) {
    std::cerr << "No override for "
                 "AbstractSocket::connect(Signal<double>*) method\n";
    throw YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE;
  }

public:
  virtual void setConstant(double k) {
    std::cerr << "No override for AbstractSocket::setConstant(double) method\n";
    throw YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE;
  }
};
