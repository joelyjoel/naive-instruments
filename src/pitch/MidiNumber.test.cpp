
#include "../dependencies/catch.hpp"

#include "MidiNumber.h"

TEST_CASE("MidiNumber enum has correct values") {
  REQUIRE(B3 == 59);
  REQUIRE(C4 == 60);
  REQUIRE(A0 == 21);
}
