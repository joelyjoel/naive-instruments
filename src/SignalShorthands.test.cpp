#include "./SignalShorthands.h"
#include "./test-framework/custom-assertions.h"

using namespace NaiveInstruments::SignalShorthands;

TEST_CASE( "Using a shorthand to create a constant" )
{
    CHECK_SIGNAL( constant( 10 ), { 10, 10, 10 } );
}

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

TEST_CASE( "Creating a sampler with a contrived buffer using a shorthand" )
{
    MonoBuffer buffer( 10 );
    buffer[0] = 5;
    buffer[1] = 4;
    buffer[2] = 3;
    buffer[3] = 2;
    buffer[4] = 1;

    auto signal = sampler( &buffer );
    CHECK_SIGNAL( signal, { 5, 4, 3, 2, 1 } );
}
