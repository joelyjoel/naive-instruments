#include "CommonPatterns.h"

LazyRegex CommonPatterns::naturalNumber("\\d+");
LazyRegex CommonPatterns::integer("[-+]? ?" + naturalNumber);
LazyRegex CommonPatterns::word("\\w+");
LazyRegex CommonPatterns::unit("%|(?:\\w+)?");
LazyRegex CommonPatterns::ignoreWhitespace("\\s*");

LazyRegex CommonPatterns::unsignedDecimal(naturalNumber + "\\." +
                                          naturalNumber);
LazyRegex CommonPatterns::unsignedPointNumber("\\." + naturalNumber);

LazyRegex CommonPatterns::number(
    "-?" + (naturalNumber | unsignedDecimal | unsignedPointNumber).bracket());

LazyRegex CommonPatterns::numberWithUnit(number.capture() + ignoreWhitespace +
                                         unit.capture());

// Control Signals
LazyRegex CommonPatterns::controlSequenceTempoInstruction(numberWithUnit + ":");
LazyRegex CommonPatterns::controlSequenceValueInstruction(numberWithUnit);
LazyRegex CommonPatterns::controlSequenceGlideInstruction("~");
LazyRegex CommonPatterns::controlSequenceRestInstruction("_");
LazyRegex CommonPatterns::controlSequenceInstruction(
    controlSequenceTempoInstruction | controlSequenceValueInstruction |
    controlSequenceGlideInstruction | controlSequenceRestInstruction);

LazyRegex CommonPatterns::controlSequence(
    (controlSequenceInstruction.capture() + ignoreWhitespace).kleene());
