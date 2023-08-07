#include "signal-processes.h"
#include "../core/MonoBuffer.h"
#include "../test-framework/custom-assertions.h"

using namespace NaiveInstruments;

TEST_CASE( "Creating a vector signal" )
{
    auto buffer    = std::make_shared<std::vector<double>>( 5 );
    ( *buffer )[0] = 5;
    ( *buffer )[1] = 4;
    ( *buffer )[2] = 3;
    ( *buffer )[3] = 2;
    ( *buffer )[4] = 1;


    std::shared_ptr<Signal<double>> signal = std::make_shared<NaiveInstruments::VectorSignal<double>>( buffer );

    CHECK_SIGNAL( signal, { 5, 4, 3, 2, 1 } );
}

TEST_CASE( "signals all have the expected number of inputs" )
{
    auto exampleBuffer = new MonoBuffer( 10 );
    REQUIRE( USaw().inputs.size() == 1 );
    REQUIRE( Sum<double>().inputs.size() == 2 );
    REQUIRE( Subtract<double>().inputs.size() == 2 );
    REQUIRE( SignFlip().inputs.size() == 1 );
    REQUIRE( Multiply().inputs.size() == 2 );
    REQUIRE( Divide().inputs.size() == 2 );
    REQUIRE( MonoToStereo().inputs.size() == 1 );
    REQUIRE( Repeater<double>().inputs.size() == 1 );
    REQUIRE( Clock<double>().inputs.size() == 0 );
    REQUIRE( Accumulator().inputs.size() == 1 );
    REQUIRE( Modulo().inputs.size() == 2 );
    REQUIRE( Noise().inputs.size() == 0 );

    // TODO: fix causing runtime exception
    /* REQUIRE( VectorSignal<double>( {} ).inputs.size() == 0 ); */

    REQUIRE( Sampler( exampleBuffer ).inputs.size() == 0 );
    REQUIRE( Wavetable( exampleBuffer ).inputs.size() == 1 );
    REQUIRE( Wait<double>( 44100 ).inputs.size() == 1 );
    REQUIRE( Skip<double>( 44100 ).inputs.size() == 1 );
    REQUIRE( IntervalToRatio().inputs.size() == 1 );
    REQUIRE( BufferLooper( 44100 ).inputs.size() == 1 );
    REQUIRE( HardClip<double>().inputs.size() == 1 );
    delete exampleBuffer;
}

TEST_CASE( "Creating a stereo vector signal" )
{
    auto buffer    = std::make_shared<std::vector<StereoFrame>>( 5 );
    ( *buffer )[0] = { 5, 0 };
    ( *buffer )[1] = { 4, 1 };
    ( *buffer )[2] = { 3, 2 };
    ( *buffer )[3] = { 2, 3 };
    ( *buffer )[4] = { 1, 4 };


    std::shared_ptr<Signal<StereoFrame>> signal =
        std::make_shared<NaiveInstruments::VectorSignal<StereoFrame>>( buffer );

    CHECK_SIGNAL( signal, { { 5, 0 }, { 4, 1 }, { 3, 2 }, { 2, 3 }, { 1, 4 } } );
}

TEST_CASE( "Creating a Sampler using a contrived MonoBuffer" )
{
    MonoBuffer buffer( 10 );
    buffer[0] = 5;
    buffer[1] = 4;
    buffer[2] = 3;
    buffer[3] = 2;
    buffer[4] = 1;

    std::shared_ptr<Signal<double>> sampler = std::make_shared<NaiveInstruments::Sampler>( &buffer );
    CHECK_SIGNAL( sampler, { 5, 4, 3, 2, 1 } );
}

TEST_CASE( "Signal processes know their own names at runtime" )
{
    REQUIRE( Sum<double>().name() == "Sum" );
    REQUIRE( Subtract<double>().name() == "Subtract" );
    REQUIRE( SignFlip().name() == "SignFlip" );
    REQUIRE( Multiply().name() == "Multiply" );
    REQUIRE( Divide().name() == "Divide" );
    REQUIRE( MonoToStereo().name() == "MonoToStereo" );
    REQUIRE( Repeater<double>().name() == "Repeater" );
    REQUIRE( Clock<double>().name() == "Clock" );
    REQUIRE( Accumulator().name() == "Accumulator" );
    REQUIRE( Modulo().name() == "Modulo" );
    REQUIRE( Noise().name() == "Noise" );
    /* REQUIRE( Sampler().name() == "Sampler" ); */
    /* REQUIRE( Wavetable().name() == "Wavetable" ); */
    REQUIRE( Wait<double>( 441 ).name() == "Wait" );
    REQUIRE( Skip<double>( 10 ).name() == "Skip" );
    REQUIRE( IntervalToRatio().name() == "IntervalToRatio" );
    REQUIRE( BufferLooper( 100 ).name() == "BufferLooper" );
    REQUIRE( HardClip<double>().name() == "HardClip" );
    REQUIRE( LinearRamp().name() == "LinearRamp" );
}

TEST_CASE( "Signal processes know their own input names at runtime" )
{
    REQUIRE( Sum<double>().a.name() == "a" );
    REQUIRE( Sum<double>().b.name() == "b" );

    REQUIRE( Subtract<double>().a.name() == "a" );
    REQUIRE( Subtract<double>().b.name() == "b" );

    REQUIRE( SignFlip().input.name() == "input" );

    REQUIRE( Multiply().a.name() == "a" );
    REQUIRE( Multiply().b.name() == "b" );

    REQUIRE( Divide().numerator.name() == "numerator" );
    REQUIRE( Divide().denominator.name() == "denominator" );

    REQUIRE( MonoToStereo().input.name() == "input" );

    REQUIRE( Repeater<double>().input.name() == "input" );

    REQUIRE( Accumulator().input.name() == "input" );

    REQUIRE( Modulo().input.name() == "input" );
    REQUIRE( Modulo().maximum.name() == "maximum" );

    /* REQUIRE( Sampler().name() == "Sampler" ); */
    /* REQUIRE( Wavetable().name() == "Wavetable" ); */

    REQUIRE( Wait<double>( 441 ).input.name() == "input" );

    REQUIRE( Skip<double>( 10 ).input.name() == "input" );

    REQUIRE( IntervalToRatio().interval.name() == "interval" );

    REQUIRE( BufferLooper( 100 ).input.name() == "input" );

    REQUIRE( HardClip<double>().input.name() == "input" );


    REQUIRE( LinearRamp().before.name() == "before" );
    REQUIRE( LinearRamp().duration.name() == "duration" );
    REQUIRE( LinearRamp().after.name() == "after" );
}
