#include "ControlSignal.h"
#include "../../dependencies/catch.hpp"
#include <iostream>

TEST_CASE("Parse valid control signals without error", "[ControlSignal]") {
  REQUIRE(ControlSignal::parse("1s: 1 ~~~~ 0").success());
}
