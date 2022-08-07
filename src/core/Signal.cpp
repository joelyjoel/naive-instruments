#include "Signal.h"

void UntypedSignalInput::sync(int clock) {
  if (hasConnection())
    connection().sync(clock);
}

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> &a, Signal<frame> &b) {
  a.connect(b);
  return b;
}

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> *a, Signal<frame> &b) {
  a->connect(b);
  return b;
}

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> &a, Signal<frame> *b) {
  a.connect(*b);
  return *b;
}

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> *a, Signal<frame> *b) {
  a->connect(*b);
  return *b;
}

template <typename frame> void operator<<(SignalInput<frame> &a, frame b) {
  a.setConstant(b);
}

template <typename frame> void operator<<(SignalInput<frame> *a, frame b) {
  a->setConstant(b);
}
