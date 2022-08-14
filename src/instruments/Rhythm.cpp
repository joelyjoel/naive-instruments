#include "Rhythm.h"

std::ostream &operator<<(std::ostream &out, Rhythm &rhythm) {
  rhythm.describe(out);
  return out;
}
