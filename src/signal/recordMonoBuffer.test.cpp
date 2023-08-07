#include "./recordMonoBuffer.h"
#include "../../dependencies/catch.hpp"
#include "./SignalShorthands.h"

TEST_CASE( "Recording a very short monobuffer from a signal" )
{
    auto recording =
        NaiveInstruments::recordMonoBuffer( NaiveInstruments::SignalShorthands::constant( 1 ), 10.0 / 44100.0 );

    REQUIRE( ( *recording )[0] == 1 );
    REQUIRE( ( *recording )[1] == 1 );
    REQUIRE( ( *recording )[2] == 1 );
    REQUIRE( ( *recording )[3] == 1 );
    REQUIRE( ( *recording )[4] == 1 );
    REQUIRE( ( *recording )[6] == 1 );
    REQUIRE( ( *recording )[7] == 1 );
    REQUIRE( ( *recording )[8] == 1 );
    REQUIRE( ( *recording )[9] == 1 );
}
