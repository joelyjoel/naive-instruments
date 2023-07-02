#include "./SignalShorthands.h"
#include "./test-framework/custom-assertions.h"

using namespace NaiveInstruments::SignalShorthands;

TEST_CASE( "creating a clock" )
{
    CHECK_SIGNAL( t(), { 0, 1, 2, 3, 4, 5 } );
}

TEST_CASE( "Adding two clocks together with function" )
{
    CHECK_SIGNAL<double>( add( t(), t() ), { 0, 2, 4, 6 } );
}

TEST_CASE( "Adding two clocks together with operator overload" )
{

    CHECK_SIGNAL( t() + t(), { 0, 2, 4, 6 } );
}
