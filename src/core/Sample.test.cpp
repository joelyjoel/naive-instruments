#include "./Sample.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("reading and writing to a sample") {

  Sample<bool> mySample(8);
  mySample.write(0, 0, true);
  REQUIRE(mySample.read(0, 0) == true);
};

TEST_CASE("Create a sample from a vector and find the peak") {
  REQUIRE(Sample<int>({1, 2, 3, 4}).peak() == 4);
}
