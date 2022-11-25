#include "./Sample.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("reading and writing to a sample") {

  Sample<bool> mySample(1, 8);
  mySample.write(0, 0, true);
  REQUIRE(mySample.read(0, 0) == true);
};
