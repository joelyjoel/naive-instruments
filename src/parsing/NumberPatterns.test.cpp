#include "../../dependencies/catch.hpp"

#include "NumberPatterns.h"
#include <string>
#include <vector>

using std::string, std::vector;

TEST_CASE( "NumberPatterns::naturalNumber accepts simple positive integers" )
{
    // Positive assertions
    REQUIRE( NumberPatterns::naturalNumber.test( "99" ) );
    REQUIRE( NumberPatterns::naturalNumber.test( "0" ) );

    // Negative assertions
    REQUIRE( !NumberPatterns::naturalNumber.test( "" ) );
    REQUIRE( !NumberPatterns::naturalNumber.test( "-1" ) );
    REQUIRE( !NumberPatterns::naturalNumber.test( "1.1" ) );
    REQUIRE( !NumberPatterns::naturalNumber.test( ".1" ) );
    REQUIRE( !NumberPatterns::naturalNumber.test( " 1.1" ) );
    REQUIRE( !NumberPatterns::naturalNumber.test( "cat" ) );
    REQUIRE( !NumberPatterns::naturalNumber.test( "99cat" ) );
}

TEST_CASE( "NumberPatterns::integer accepts only zero and positive and negative "
           "numbers" )
{
    REQUIRE( NumberPatterns::integer.test( "0" ) );
    REQUIRE( NumberPatterns::integer.test( "1" ) );
    REQUIRE( NumberPatterns::integer.test( "-1" ) );
    REQUIRE( NumberPatterns::integer.test( "999" ) );
    REQUIRE( NumberPatterns::integer.test( "-999" ) );

    // Negative assertions
    REQUIRE( !NumberPatterns::integer.test( "-999.0" ) );
    REQUIRE( !NumberPatterns::integer.test( "0.9" ) );
}

TEST_CASE( "CommonPaterns:unsignedDecimal accepts unsigned numbers with decimal "
           "point" )
{
    REQUIRE( NumberPatterns::unsignedDecimal.test( "0.0" ) );
    REQUIRE( NumberPatterns::unsignedDecimal.test( "100.0" ) );
    REQUIRE( NumberPatterns::unsignedDecimal.test( "3.14" ) );

    REQUIRE( !NumberPatterns::unsignedDecimal.test( "-100.0" ) );
    REQUIRE( !NumberPatterns::unsignedDecimal.test( "100" ) );
    REQUIRE( !NumberPatterns::unsignedDecimal.test( ".2" ) );
}

TEST_CASE( "CommonPaterns:unsignedPointNumber accepts unsigned numbers that "
           "begin with decimal "
           "point" )
{
    REQUIRE( !NumberPatterns::unsignedPointNumber.test( "0.0" ) );
    REQUIRE( !NumberPatterns::unsignedPointNumber.test( "100.0" ) );
    REQUIRE( !NumberPatterns::unsignedPointNumber.test( "3.14" ) );

    REQUIRE( !NumberPatterns::unsignedPointNumber.test( "-100.0" ) );
    REQUIRE( !NumberPatterns::unsignedPointNumber.test( "100" ) );
    REQUIRE( NumberPatterns::unsignedPointNumber.test( ".2" ) );
    REQUIRE( NumberPatterns::unsignedPointNumber.test( ".02" ) );
    REQUIRE( NumberPatterns::unsignedPointNumber.test( ".0" ) );
}

TEST_CASE( "number accepts any number" )
{
    vector<string> validNumberStrings = { "0", "10", "-0", "-10", "0.0", ".0", ".0123", "-.55", "-.45" };
    for ( auto& str : validNumberStrings )
        REQUIRE( NumberPatterns::number.test( str ) );
}

TEST_CASE( "NumberPatterns::parseNumber" )
{
    REQUIRE( NumberPatterns::parseNumber( "55" ) == 55 );
    REQUIRE( NumberPatterns::parseNumber( "0" ) == 0 );
    REQUIRE( NumberPatterns::parseNumber( "-.45" ) == -.45 );
}
