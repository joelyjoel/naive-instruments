#include "Signal.h"

void UntypedSignalInput::reset() {
  if (hasConnection())
    untypedConnection->reset();
}

/**
 * Synchronise the plugged instrument with the owner
 */
template <> double SignalInput<double>::sync() {
  if (connection)
    return connection->tickUntil(owner->internalClock);
  else
    return constant;
}
