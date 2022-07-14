#include "BreakpointEnvelope.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("An empty BreakpointEnvelope has duration = 0") {
  BreakpointEnvelope be;
  REQUIRE(be.duration() == 0);
}

TEST_CASE("An non empty BreakpointEnvelope has duration > 0") {
  BreakpointEnvelope be;
  be.addHold(1);
  REQUIRE(be.duration() == 1);
}
