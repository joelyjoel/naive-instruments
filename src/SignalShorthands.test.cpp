#include "./SignalShorthands.h"
#include "../dependencies/catch.hpp"

using namespace SignalShorthands;

TEST_CASE( "creating a clock" )
{
    auto clock = t();
    clock->sync( 1 );
    REQUIRE( clock->output == 1 );
}
