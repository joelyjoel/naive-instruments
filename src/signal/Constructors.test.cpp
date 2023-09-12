#include "./Constructors.h"
#include "../test-framework/custom-assertions.h"

TEST_CASE( "Can use StandardSignalConstructor to create Noise process" )
{
    NaiveInstruments::StandardSignalConstructor constructor;
    auto                                        result = constructor.construct( "noise" );

    CHECK( typeid( *result ) == typeid( NaiveInstruments::Noise ) );
    CHECK( constructor.recognise( result ) == "noise" );
}


TEST_CASE( "StandardSignalConstructor can recognise the signals it constructs" )
{
    auto                                        shorthand = GENERATE( "usaw",
                               "sum",
                               "subtract",
                               "signFlip",
                               "multiply",
                               "divide",
                               "repeater",
                               "clock",
                               "accumulator",
                               "modulo",
                               "noise",
                               "hardClip",
                               "linearRamp",
                               "sequence" );
    NaiveInstruments::StandardSignalConstructor constructor;
    auto                                        signal = constructor.construct( shorthand );
    CAPTURE( shorthand, typeid( signal ).name() );
    CHECK( constructor.recognise( signal ) == shorthand );
}
