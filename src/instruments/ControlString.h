#include "../core.h"
#include "./BreakpointEnvelope.h"
#include "../parsing/NumberWithUnit.h"
#include "../parsing/LazyRegex.h"

class ControlString : public BreakpointEnvelope {

public:
  static LazyRegex controlSequenceTempoInstruction;
  static LazyRegex controlSequenceValueInstruction;
  static LazyRegex controlSequenceGlideInstruction;
  static LazyRegex controlSequenceRestInstruction;
  static LazyRegex controlSequenceInstruction;
  static LazyRegex controlSequence;
};
