#include "ControlString.h"

// Control Signals

LazyRegex ControlString::TempoInstruction::pattern( NumberWithUnit::pattern.bracket() + ":" );

LazyRegex ControlString::ValueInstruction::pattern( NumberWithUnit::pattern );

LazyRegex ControlString::SustainStepInstruction::pattern( "[~_]" );

/* LazyRegex ControlString::anyInstructionPattern((TempoInstruction::pattern |
 */
/*                                                 ValueInstruction::pattern |
 */
/*                                                 SustainStepInstruction::pattern)
 */
/*                                                    .noCaptures()); */

LazyRegex ControlString::anyInstructionPattern( "(?:[-+]?(?:\\d*\\.)?\\d+[a-zA-Z%]*:?)|[~_]" );

LazyRegex ControlString::firstInstructionPattern( "^" + ControlString::anyInstructionPattern.capture()
                                                  + LazyRegex::ignoreWhitespace );

LazyRegex ControlString::pattern( ( anyInstructionPattern.capture() + LazyRegex::ignoreWhitespace ).kleene() );
