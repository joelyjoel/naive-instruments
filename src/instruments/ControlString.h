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

    static Hopefully<float> parse(const string &str) {
      if (pattern.test(str)) {
        return NumberWithUnit::parseInterval(str.substr(0, str.size() - 1));
      } else
        return Disappointment;
    }
  };

  class ValueInstruction {
  public:
    static LazyRegex pattern;

    static Hopefully<float> parse(const string &str) {
      if (pattern.test(str)) {
        auto nu = NumberWithUnit::parse(str);
        // TODO: Clearly this needs work
        if (nu.success() && nu->unit == Units::noUnit)
          return nu->number;
        else
          return Disappointment;

      } else
        return Disappointment;
    }
  };

  class SustainStepInstruction {
  public:
    static LazyRegex pattern;

    typedef enum { Resting, Gliding } SustainKind;

    static Hopefully<SustainKind> parse(const string &str) {
      if (str == "~")
        return Gliding;
      else if (str == "_")
        return Resting;
      else
        return Disappointment;
    }
  };

  static LazyRegex anyInstructionPattern;
  static LazyRegex pattern;
};
