#include "../../dependencies/catch.hpp"

#include "../lib.h"

TEST_CASE("listing signal inputs") {
  shared_ptr<Add> adder = make_shared<Add>();
  shared_ptr<Sine> sin1 = make_shared<Sine>();
  shared_ptr<Sine> sin2 = make_shared<Sine>();

  REQUIRE(adder->inputSignals().size() == 0);

  adder->a << sin1;

  auto inputs = adder->inputSignals();
  REQUIRE(inputs[0] == sin1);
  REQUIRE(inputs.size() == 1);

  adder->b << sin2;

  auto inputs2 = adder->inputSignals();
  REQUIRE(inputs2[0] == sin1);
  REQUIRE(inputs2[1] == sin2);
  REQUIRE(inputs2.size() == 2);
}
