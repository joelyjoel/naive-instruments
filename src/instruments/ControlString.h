#include "../parsing/LazyRegex.h"
#include "../parsing/NumberWithUnit.h"
#include "./BreakpointEnvelope.h"
#include <string>

using std::string;

class ControlString : public BreakpointEnvelope {

public:
  class TempoInstruction {
  public:
    static LazyRegex pattern;

    Hopefully<float> parse(const string &str) {
      if (pattern.test(str)) {
        return NumberWithUnit::parseInterval(str.substr(0, -1));
      } else
        return Disappointment;
    }
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
