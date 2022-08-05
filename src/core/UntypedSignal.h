#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

class UntypedSignalInput;
template <typename SignalFrame> class SignalInput;

/**
 * This class just exists so that SignalInput's don't have to know the
 * SignalFrame type of their owners.
 */
class UntypedSignal {
public:
  int internalClock = 0;

protected:
  std::vector<UntypedSignalInput *> inputs;

protected:
  template <typename SignalFrame>
  SignalInput<SignalFrame> &addInput(double initValue = 0) {
    auto signalInput = new SignalInput<SignalFrame>(this);
    inputs.push_back(signalInput);
    return *signalInput;
  }

public:
  virtual std::string label() { return "Signal"; }
  std::string summary() {
    return label() + "@" + std::to_string(internalClock);
  }

public:
  /**
   * Naive instruments work a bit like clock work. Every frame of the digital
   * signal they "tick". What they actually do when they tick is up to them!
   */
  virtual void tick() {
    std::cerr
        << "Oh no, looks like the programmer forgot to implement the tick "
           "method for a Signal\n";
    throw 1;
  }

protected:
  /**
   * Reset the internal state of the Signal. Stateless signals will NOT
   * override this method
   */
  virtual void resetState() {
    // noop
  }

public:
  void reset() {
    resetState();
    // TODO: Reset all the inputs too
  }
};
