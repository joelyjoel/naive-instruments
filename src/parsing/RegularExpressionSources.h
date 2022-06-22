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

  const string Or(const string &a, const string &b) {
    return Bracket(a) + "|" + Bracket(b);
  }
  const string Or(const string &a, const string &b, const string &c) {
    return Bracket(a) + "|" + Bracket(b) + "|" + Bracket(c);
  }

public:
  const string naturalNumber = "\\d+";
  const string integer = "(-|+)? ?" + naturalNumber;
  const string word = "\\w+";
  const string ignoreWhitespace = "\\s*";

private:
  const string positiveDecimal = naturalNumber + "\\." + naturalNumber;
  const string positivePointNumber = "\\." + naturalNumber;

public:
  const string number =
      "-?" + Bracket(Or(naturalNumber, positiveDecimal, positivePointNumber));

  const string numberWithUnit =
      Capture(number) + ignoreWhitespace + Capture("\\w*");
};
