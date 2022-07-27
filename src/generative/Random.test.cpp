#include "../../dependencies/catch.hpp"

#include "Random.h"

TEST_CASE("Random class generates expected numbers when seed = 1") {
  const long seed = 1;
  Random random(seed);

  const std::vector<long> expectedValues = {
      35651601,           1130297953386881, -9204155787274874573,
      143006948545953793, 530110192467034,  569735658174708356,
  };

  for (long expectedValue : expectedValues) {
    REQUIRE(random.next() == expectedValue);
  }
}

TEST_CASE(
    "Random class generates consistent numbers when using matching seed") {

  const int numberOfIterations = 256;
  std::vector<long> seeds{1, 405, 2403495, 209783};
  for (long seed : seeds) {
    Random random1(seed), random2(seed);
    for (int i = 0; i < numberOfIterations; ++i)
      REQUIRE(random1.next() == random2.next());
  }
}
