#include "NumberPatterns.h"

LazyRegex NumberPatterns::naturalNumber("\\d+");
LazyRegex NumberPatterns::integer("[-+]? ?" + naturalNumber);
// LazyRegex NumberPatterns::word("\\w+");
LazyRegex NumberPatterns::unit("%|(?:\\w+)?");
LazyRegex NumberPatterns::ignoreWhitespace("\\s*");

LazyRegex NumberPatterns::unsignedDecimal(naturalNumber + "\\." +
                                          naturalNumber);
LazyRegex NumberPatterns::unsignedPointNumber("\\." + naturalNumber);

LazyRegex NumberPatterns::number(
    "-?" + (naturalNumber | unsignedDecimal | unsignedPointNumber).bracket());

LazyRegex NumberPatterns::numberWithUnit(number.capture() + ignoreWhitespace +
                                         unit.capture());

// Control Signals
LazyRegex NumberPatterns::controlSequenceTempoInstruction(numberWithUnit + ":");
LazyRegex NumberPatterns::controlSequenceValueInstruction(numberWithUnit);
LazyRegex NumberPatterns::controlSequenceGlideInstruction("~");
LazyRegex NumberPatterns::controlSequenceRestInstruction("_");
LazyRegex NumberPatterns::controlSequenceInstruction(
    controlSequenceTempoInstruction | controlSequenceValueInstruction |
    controlSequenceGlideInstruction | controlSequenceRestInstruction);

LazyRegex NumberPatterns::controlSequence(
    (controlSequenceInstruction.capture() + ignoreWhitespace).kleene());
