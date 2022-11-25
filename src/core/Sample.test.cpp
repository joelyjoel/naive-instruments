#include "./Sample.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("reading and writing to a sample") {

  Sample<bool> mySample(8);
  mySample.write(0, 0, true);
  REQUIRE(mySample.read(0, 0) == true);
};

// TODO: Bounds errors are thrown when accessing out of bounds
// TODO: Reading and writing multichannel samples
// TODO: Tests including large amounts of data

TEST_CASE("Create a sample from a vector and find the peak") {
  REQUIRE(Sample<int>({1, 2, 3, 4}).peak() == 4);
}

TEST_CASE("Overwrite a region of one sample using another") {
  Sample<int> master(8);
  Sample<int> overdub({1, 2, 3, 4});
  master.write(overdub);
  REQUIRE(master.read(0, 1) == 2);
};

TEST_CASE("Overrwriting a region using another sample and an offset") {
  Sample<int> master(8);
  Sample<int> overdub({1, 2, 3, 4});
  master.write(overdub, 2);
  REQUIRE(master.read(0, 1) == 0);
  REQUIRE(master.read(0, 2) == 1);
  REQUIRE(master.read(0, 5) == 4);
}
