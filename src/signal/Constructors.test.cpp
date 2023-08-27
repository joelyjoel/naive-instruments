#include "./Constructors.h"
#include "../test-framework/custom-assertions.h"

TEST_CASE( "Can use StandardSignalConstructor to create Noise process" )
{
    NaiveInstruments::StandardSignalConstructor constructor;
    auto                                        result = constructor.construct( "noise" );

    CHECK( typeid( *result ) == typeid( NaiveInstruments::Noise ) );
}


/* TEST_CASE( "StandardSignalConstructor can recognise the signals it constructs" ) */
/* { */
/*     auto                                        shorthand = "noise"; */
/*     NaiveInstruments::StandardSignalConstructor constructor; */
/*     auto                                        signal = constructor.construct( shorthand ); */
/*     CAPTURE( shorthand, typeid( *signal ).name() ); */
/*     CHECK( constructor.recognise( *signal ) == shorthand ); */
/* } */
