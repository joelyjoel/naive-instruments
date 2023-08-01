#include "./naming.h"
#include "../../dependencies/catch.hpp"

TEST_CASE( "Named things with templated string literals" )
{
    WithName<"Hello"> hello;

    REQUIRE( hello.name() == "Hello" );
}
