#include "../core.h"
#include "LazyRegex.h"

class NumberPatterns {
public:
  static LazyRegex naturalNumber;
  static LazyRegex integer;
  static LazyRegex ignoreWhitespace;

  static LazyRegex unsignedDecimal;
  static LazyRegex unsignedPointNumber;

  static LazyRegex number;

  // TODO: Move these two to relevant classes
  static LazyRegex unit;
  static LazyRegex numberWithUnit;

  // Control Signals
  // TODO: Move these to controlSequence class
private:
  static LazyRegex controlSequenceTempoInstruction;
  static LazyRegex controlSequenceValueInstruction;
  static LazyRegex controlSequenceGlideInstruction;
  static LazyRegex controlSequenceRestInstruction;
  static LazyRegex controlSequenceInstruction;
  static LazyRegex controlSequence;

public:
  static Hopefully<float> parseNumber(const std::string &str) {
    if (number.test(str))
      return stof(str);
    else
      return Disappointment;
  }
};
