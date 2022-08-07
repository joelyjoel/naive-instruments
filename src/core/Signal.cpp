#include "Signal.h"

void UntypedSignalInput::sync(int clock) {
  if (hasConnection())
    connection().sync(clock);
}
