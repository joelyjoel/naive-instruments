
#include "BreakpointEnvelopeSequencer.h"

// Control Signals

LazyRegex NaiveInstruments::ControlString::TempoInstruction::pattern( NumberWithUnit::pattern.bracket() + ":" );

LazyRegex NaiveInstruments::ControlString::ValueInstruction::pattern( NumberWithUnit::pattern );

LazyRegex NaiveInstruments::ControlString::SustainStepInstruction::pattern( "[~_]" );

/* LazyRegex ControlString::anyInstructionPattern((TempoInstruction::pattern |
 */
/*                                                 ValueInstruction::pattern |
 */
/*                                                 SustainStepInstruction::pattern)
 */
/*                                                    .noCaptures()); */

LazyRegex NaiveInstruments::ControlString::anyInstructionPattern( "(?:[-+]?(?:\\d*\\.)?\\d+[a-zA-Z%]*:?)|[~_]" );

LazyRegex NaiveInstruments::ControlString::firstInstructionPattern( "^" + ControlString::anyInstructionPattern.capture()
                                                                    + LazyRegex::ignoreWhitespace );

LazyRegex NaiveInstruments::ControlString::pattern(
    ( anyInstructionPattern.capture() + LazyRegex::ignoreWhitespace ).kleene() );
