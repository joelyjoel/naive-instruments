
#include "BreakpointEnvelope.h"
std::ostream &operator<<(std::ostream &out, const BreakpointEnvelope &B) {
  for (auto section : B.sections) {
    out << section.duration << "s:" << section.startValue << "~"
        << section.endValue << " ";
  }
  return out;
}
