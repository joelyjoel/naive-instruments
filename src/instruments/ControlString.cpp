#include "ControlString.h"

// Control Signals

LazyRegex ControlString::TempoInstruction::pattern(
    NumberWithUnit::pattern.bracket() + ":");

LazyRegex ControlString::ValueInstruction::pattern(NumberWithUnit::pattern);

LazyRegex ControlString::SustainStepInstruction::pattern("[~_]");

LazyRegex ControlString::anyInstructionPattern(TempoInstruction::pattern |
                                               ValueInstruction::pattern |
                                               SustainStepInstruction::pattern);

LazyRegex ControlString::pattern(
    (anyInstructionPattern.capture() + LazyRegex::ignoreWhitespace).kleene());
