#include "Signal.h"

void UntypedSignalInput::reset() {
  if (hasConnection())
    untypedConnection->reset();
}

void UntypedSignalInput::sync(int clock) {
  if (hasConnection())
    untypedConnection->sync(clock);
}
