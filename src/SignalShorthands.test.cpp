#include "./SignalShorthands.h"
#include "./test-framework/custom-assertions.h"

using namespace SignalShorthands;

TEST_CASE( "creating a clock" )
{
    auto clock = t();
    CHECK_SIGNAL( clock, { 0, 1, 2, 3, 4, 5 } );
}
