#include "../dependencies/catch.hpp"

#include "Pitch.h"

TEST_CASE("Pitch classes are correct") {
  REQUIRE(Pitch::C == 0);
  REQUIRE(Pitch::Db == 1);
  REQUIRE(Pitch::D == 2);
  REQUIRE(Pitch::Eb == 3);
  REQUIRE(Pitch::E == 4);
  REQUIRE(Pitch::F == 5);
  REQUIRE(Pitch::Gb == 6);
  REQUIRE(Pitch::G == 7);
  REQUIRE(Pitch::Ab == 8);
  REQUIRE(Pitch::A == 9);
  REQUIRE(Pitch::Bb == 10);
  REQUIRE(Pitch::B == 11);
}
