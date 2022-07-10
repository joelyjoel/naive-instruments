#include "../parsing/LazyRegex.h"
#include "../parsing/NumberWithUnit.h"
#include "./BreakpointEnvelope.h"

class ControlString : public BreakpointEnvelope {

public:
  class TempoInstruction {
  public:
    static LazyRegex pattern;
  };

  class ValueInstruction {
  public:
    static LazyRegex pattern;
  };

  class SustainStepInstruction {
  public:
    static LazyRegex pattern;
  };

  static LazyRegex anyInstructionPattern;
  static LazyRegex pattern;
};
