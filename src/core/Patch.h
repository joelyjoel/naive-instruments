#pragma once

#include "Signal.h"
#include "SignalInput.h"
#include <string>

template <typename SignalFrame> class Patch : public Signal<SignalFrame> {
private:
  Signal<SignalFrame> &output;

public:
  Patch(Signal<SignalFrame> &output) : output(output) {}

  void tick() {
    Signal<SignalFrame>::out(output.tickUntil(UntypedSignal::internalClock));
  }

protected:
  template <typename T> SignalInput<T> &exposeSocket(SignalInput<T> &socket) {
    Signal<SignalFrame>::sockets.push_back(&socket);
    return socket;
  }

  std::string label() { return "Patch"; }
};
