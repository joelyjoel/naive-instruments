#pragma once

#include <string>
#include <vector>

using std::string, std::vector;

/**
 * NOTE: Use as singleton
 */
class RegularExpressionSources {
  // TODO: use a new class ComposableRegex for all these definitions
private:
  static const string Bracket(const string &operand) {
    return "(?:" + operand + ")";
  }
  static const string Capture(const string &operand) {
    return "(" + operand + ")";
  }
  static const string Optional(const string &operand) {
    return Bracket(operand) + "?";
  }
  static const string Kleene(const string &operand) {
    return Bracket(operand) + "*";
  }

  static const string Or(const string &a, const string &b) {
    return Bracket(a) + "|" + Bracket(b);
  }
  static const string Or(const string &a, const string &b, const string &c) {
    return Bracket(a) + "|" + Bracket(b) + "|" + Bracket(c);
  }
  static const string Or(const string &a, const string &b, const string &c,
                         const string &d) {
    return Bracket(a) + "|" + Bracket(b) + "|" + Bracket(c) + "|" + Bracket(d);
  }

public:
  static const string naturalNumber;
  static const string integer;
  static const string word;
  static const string unit;
  static const string ignoreWhitespace;

private:
  static const string positiveDecimal;
  static const string positivePointNumber;

public:
  static const string number;

  static const string numberWithUnit;

  // Control Signals
private:
  static const string controlSequenceTempoInstruction;
  static const string controlSequenceValueInstruction;
  static const string controlSequenceInstruction;

public:
  static const string controlSequenceSustainInstruction;
  static const string controlSequence;
};
