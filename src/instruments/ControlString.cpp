#include "ControlString.h"

// Control Signals
LazyRegex ControlString::controlSequenceTempoInstruction(
    NumberWithUnit::pattern + ":");
LazyRegex
    ControlString::controlSequenceValueInstruction(NumberWithUnit::pattern);
LazyRegex ControlString::controlSequenceGlideInstruction("~");
LazyRegex ControlString::controlSequenceRestInstruction("_");
LazyRegex ControlString::controlSequenceInstruction(
    controlSequenceTempoInstruction | controlSequenceValueInstruction |
    controlSequenceGlideInstruction | controlSequenceRestInstruction);

LazyRegex ControlString::controlSequence((controlSequenceInstruction.capture() +
                                          LazyRegex::ignoreWhitespace)
                                             .kleene());
