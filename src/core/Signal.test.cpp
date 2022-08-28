#include "../../dependencies/catch.hpp"

#include "../lib.h"

TEST_CASE("listing signal inputs") {
  Add adder;
  Sine sin1, sin2;

  REQUIRE(adder.inputSignals().size() == 0);

  adder.a << sin1;

  auto inputs = adder.inputSignals();
  REQUIRE(inputs[0] == &sin1);
  REQUIRE(inputs.size() == 1);

  adder.b << sin2;

  auto inputs2 = adder.inputSignals();
  REQUIRE(inputs2[0] == &sin1);
  REQUIRE(inputs2[1] == &sin2);
  REQUIRE(inputs2.size() == 2);
}
