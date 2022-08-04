#pragma once

#include "Signal.h"
#include "Socket.h"
#include <string>

template <typename SignalFrame> class Patch : public Signal<SignalFrame> {
private:
  Signal<SignalFrame> &output;

public:
  Patch(Signal<SignalFrame> &output) : output(output) {}

  SignalFrame tick() { return output.tickUntil(UntypedSignal::internalClock); }

protected:
  template <typename T> SignalInput<T> &exposeSocket(SignalInput<T> &socket) {
    Signal<SignalFrame>::sockets.push_back(&socket);
    return socket;
  }

  std::string label() { return "Patch"; }
};
