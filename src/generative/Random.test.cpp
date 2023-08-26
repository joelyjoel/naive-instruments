#include "../../dependencies/catch.hpp"

#include "Random.h"

TEST_CASE( "Random class generates expected numbers when seed = 1" )
{
    const long seed = 1;
    Random     random( seed );

    const std::vector<uint64_t> expectedValues = {
        1082269761,
        1152992998833853505,
    };

    for ( long expectedValue : expectedValues )
    {
        REQUIRE( random.next() == expectedValue );
    }
}

TEST_CASE( "Random class generates consistent numbers when using matching seed" )
{

    const int         numberOfIterations = 256;
    std::vector<long> seeds{ 1, 405, 2403495, 209783 };
    for ( long seed : seeds )
    {
        Random random1( seed ), random2( seed );
        for ( int i = 0; i < numberOfIterations; ++i )
            REQUIRE( random1.next() == random2.next() );
    }
}

TEST_CASE( "random item from vector of strings should always be a member of the input vector" )
{
    Random r;
    for ( int i = 0; i < 10; ++i )
    {
        auto result = r( { "a", "b", "c" } );
        CAPTURE( i, result );
        if ( result != "a" && result != "b" && result != "c" )
            FAIL( "Expected \"a\", \"b\" or \"c\"" );
    }
}
