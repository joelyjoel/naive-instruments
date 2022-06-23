#include <string>
#include <vector>

using std::string, std::vector;

/**
 * NOTE: Use as singleton
 */
class RegularExpressionSources {
private:
  const string Bracket(const string &operand) { return "(?:" + operand + ")"; }
  const string Capture(const string &operand) { return "(" + operand + ")"; }
  const string Optional(const string &operand) {
    return Bracket(operand) + "?";
  }
  const string Kleene(const string &operand) { return Bracket(operand) + "*"; }

  const string Or(const string &a, const string &b) {
    return Bracket(a) + "|" + Bracket(b);
  }
  const string Or(const string &a, const string &b, const string &c) {
    return Bracket(a) + "|" + Bracket(b) + "|" + Bracket(c);
  }
  const string Or(const string &a, const string &b, const string &c,
                  const string &d) {
    return Bracket(a) + "|" + Bracket(b) + "|" + Bracket(c) + "|" + Bracket(d);
  }

public:
  const string naturalNumber = "\\d+";
  const string integer = "(-|+)? ?" + naturalNumber;
  const string word = "\\w+";
  const string unit = "%|(?:\\w+)?";
  const string ignoreWhitespace = "\\s*";

private:
  const string positiveDecimal = naturalNumber + "\\." + naturalNumber;
  const string positivePointNumber = "\\." + naturalNumber;

public:
  const string number =
      "-?" + Bracket(Or(naturalNumber, positiveDecimal, positivePointNumber));

  const string numberWithUnit =
      Capture(number) + ignoreWhitespace + Capture(unit);

  // Control Signals
private:
  const string controlSequenceTempoInstruction = numberWithUnit + ":";
  const string controlSequenceValueInstruction = numberWithUnit;
  const string controlSequenceGlideInstruction = "~";
  const string controlSequenceRestInstruction = "_";
  const string controlSequenceInstruction =
      Or(controlSequenceTempoInstruction, controlSequenceValueInstruction,
         controlSequenceGlideInstruction, controlSequenceRestInstruction);

public:
  const string controlSequence =
      Kleene(Capture(controlSequenceInstruction) + ignoreWhitespace);
};
