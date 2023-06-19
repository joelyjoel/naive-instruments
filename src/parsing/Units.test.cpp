#include "Units.h"
#include "../../dependencies/catch.hpp"
#include <vector>

using std::vector, std::string;

TEST_CASE( "Unit::pattern recognises unit strings" )
{

    vector<string> validUnits = { "seconds",
                                  "ms",
                                  "milliseconds",
                                  "min",
                                  "minutes",
                                  "h",
                                  "hours",
                                  "smp",
                                  "zx",
                                  "Hz",
                                  "hertz",
                                  "bpm",
                                  "midi",
                                  "octave",
                                  "octaves",
                                  "st",
                                  "%" };

    for ( auto str : validUnits )
        REQUIRE( Units::pattern.test( str ) );
}
