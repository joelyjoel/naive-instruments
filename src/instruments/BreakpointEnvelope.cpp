#include "BreakpointEnvelope.h"
std::ostream &operator<<(std::ostream &out, const BreakpointEnvelope &B) {
  for (int i = 0; i < B.sections.size(); ++i) {
    const auto previous = i > 0 ? &B.sections[i - 1] : nullptr;
    const auto next = i + 1 < B.sections.size() ? &B.sections[i + 1] : nullptr;
    B.sections[i].describe(out, previous, next);
  }
  /* else */
  /*   out << B.lastEndValue(); */
  return out;
}

std::ostream &operator<<(std::ostream &out,
                         const BreakpointEnvelope::Section &section) {
  section.describe(out);
  return out;
}
