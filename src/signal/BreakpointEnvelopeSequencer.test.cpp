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


TEST_CASE( "ControlString::TempoInstruction::pattern" )
{
    REQUIRE( ControlString::TempoInstruction::pattern.test( "106bpm:" ) );
    REQUIRE( ControlString::TempoInstruction::pattern.test( "1Hz:" ) );
    REQUIRE( ControlString::TempoInstruction::pattern.test( ".25s:" ) );
}

TEST_CASE( "ControlSTring::ValueInstruction::pattern" )
{
    REQUIRE( ControlString::ValueInstruction::pattern.test( "100Hz" ) );
    REQUIRE( ControlString::ValueInstruction::pattern.test( "54" ) );
    REQUIRE( !ControlString::ValueInstruction::pattern.test( "99s:" ) );
}

TEST_CASE( "Value instruction doesn't match sustain characters" )
{
    REQUIRE( !ControlString::ValueInstruction::pattern.test( "_" ) );
    REQUIRE( !ControlString::ValueInstruction::pattern.test( "55_" ) );
}

TEST_CASE( "ControlString::SustainStepInstruction::pattern" )
{
    REQUIRE( ControlString::SustainStepInstruction::pattern.test( "~" ) );
    REQUIRE( ControlString::SustainStepInstruction::pattern.test( "_" ) );
}

TEST_CASE( "ControlString::anyInstructionPattern" )
{
    REQUIRE( ControlString::anyInstructionPattern.test( "106bpm:" ) );
    REQUIRE( ControlString::anyInstructionPattern.test( "1Hz:" ) );
    REQUIRE( ControlString::anyInstructionPattern.test( ".25s:" ) );
    REQUIRE( ControlString::anyInstructionPattern.test( "~" ) );
    REQUIRE( ControlString::anyInstructionPattern.test( "_" ) );
    REQUIRE( ControlString::anyInstructionPattern.test( "100Hz" ) );
    REQUIRE( ControlString::anyInstructionPattern.test( "54" ) );
}

TEST_CASE( "ControlString::pattern" )
{
    REQUIRE( ControlString::pattern.test( "1~~~0" ) );
    REQUIRE( ControlString::pattern.test( "100_ 200_ 100_ 200_" ) );
}

TEST_CASE( "Parsing tempo instructions" )
{
    REQUIRE( *ControlString::TempoInstruction::parse( "120bpm:" ) == .5 );
    REQUIRE( *ControlString::TempoInstruction::parse( "500ms:" ) == .5 );
    REQUIRE( *ControlString::TempoInstruction::parse( ".5s:" ) == .5 );
    REQUIRE( *ControlString::TempoInstruction::parse( "0.5 seconds:" ) == .5 );
    REQUIRE( *ControlString::TempoInstruction::parse( "2Hz:" ) == .5 );
}

TEST_CASE( "Parsing value instructions" )
{
    REQUIRE( *ControlString::ValueInstruction::parse( "12" ) == 12 );
}

TEST_CASE( "Parsing sustain instructions" )
{
    REQUIRE( *ControlString::SustainStepInstruction::parse( "~" ) == ControlString::SustainStepInstruction::Gliding );
    REQUIRE( *ControlString::SustainStepInstruction::parse( "_" ) == ControlString::SustainStepInstruction::Resting );
}

TEST_CASE( "ControlString::pattern has only one capture group" )
{
    REQUIRE( ControlString::pattern.countCaptures() == 1 );
}

TEST_CASE( "Parsing a whole (simple) control string" )
{
    auto sequence = ControlString::parse( "55___" );
    REQUIRE( sequence->durationInSamples() > 0 );
}

TEST_CASE( "Using a control string to create reference tones" )
{
    std::shared_ptr<Signal<double>> controlSignal = ControlString::parse( "55___" );
    CHECK_FRAME( controlSignal, 0, 55 );
    CHECK_FRAME( controlSignal, 100, 55 );
}
