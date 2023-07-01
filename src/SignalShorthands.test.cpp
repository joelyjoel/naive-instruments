#include "./SignalShorthands.h"
#include "./test-framework/custom-assertions.h"

using namespace SignalShorthands;

TEST_CASE( "creating a clock" )
{
    CHECK_SIGNAL( t(), { 0, 1, 2, 3, 4, 5 } );
}

TEST_CASE( " Clock + clock" )
{
    CHECK_SIGNAL<double>( add( t(), t() ), { 0, 2, 4, 6 } );
}
