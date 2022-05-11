#pragma once

#include "NaiveInstrument.h"
#include "Socket.h"

template <typename SignalFrame>
class Patch : public NaiveInstrument<SignalFrame> {
private:
  NaiveInstrument<SignalFrame> &output;

public:
  Patch(NaiveInstrument<SignalFrame> &output) : output(output) {}

  SignalFrame tick() { return output.tickUntil(this->internalClock); }

protected:
  template <typename T> Socket<T> &exposeSocket(Socket<T> &socket) {
    return socket;
  }
};
