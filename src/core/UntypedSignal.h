#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

class UntypedSignalInput;
template <typename SignalFrame> class SignalInput;

/**
 * This class just exists so that sockets don't have to know the SignalFrame
 * type of their owners.
 */
class UntypedSignal {
public:
  int internalClock = 0;

protected:
  std::vector<UntypedSignalInput *> sockets;

protected:
  template <typename SignalFrame>
  SignalInput<SignalFrame> &addSocket(double initValue = 0) {
    auto socket = new SignalInput<SignalFrame>(this);
    sockets.push_back(socket);
    return *socket;
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
};
