#include "../../dependencies/catch.hpp"

#include "../lib.h"

TEST_CASE("listing signal inputs") {
  shared_ptr<Add> adder = make_shared<Add>();
  shared_ptr<Osc> sin1 = Osc::create_sine();
  shared_ptr<Osc> sin2 = Osc::create_sine();

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
