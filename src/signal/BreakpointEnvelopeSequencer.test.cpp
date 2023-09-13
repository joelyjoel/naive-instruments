#include "./BreakpointEnvelopeSequencer.h"
#include "../test-framework/custom-assertions.h"

using namespace NaiveInstruments;

TEST_CASE( "Sequencing a breakpoint envelope step by step using BreakpointEnvelopeSequencer" )
{
    BreakpointEnvelopeSequencer sequencer;
    sequencer.addStep( 220, 220, 1 ).addStep( 220, 100, .1 ).addStep( 500 ).addStep( 50 ).addStep( 1000 );
    auto signal = NaiveInstruments::SignalShorthands::triangle( sequencer.sequence );
    referenceToneTest( "breakpointEnvelope test 2", signal, 5 );
}
