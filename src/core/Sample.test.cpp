#include "./Sample.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("reading and writing to a sample") {

  Sample<bool> mySample(8);
  mySample.write(true, 0, 0);
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
  REQUIRE(master.read(1) == 2);
};

TEST_CASE("Overrwriting a region using another sample and an offset") {
  Sample<int> master(8);
  Sample<int> overdub({1, 2, 3, 4});
  master.write(overdub, 2);
  REQUIRE(master.read(1) == 0);
  REQUIRE(master.read(2) == 1);
  REQUIRE(master.read(5) == 4);
}

TEST_CASE("Concatenating two samples") {
  Sample<int> first({1, 2, 3, 4});
  Sample<int> second({5, 6, 7, 8});

  auto combined = Sample<int>::concat(first, second);
  REQUIRE(combined->read(7) == 8);
  REQUIRE(combined->read(0) == 1);
}

TEST_CASE("Mixing two samples together") {
  Sample<int> master({1, 1, 1, 1, 1});
  Sample<int> overdub({0, 1, 2, 3, 4});

  master.mix(overdub);

  REQUIRE(master.read(0) == 1);
  REQUIRE(master.read(1) == 2);
  REQUIRE(master.read(2) == 3);
  REQUIRE(master.read(3) == 4);
  REQUIRE(master.read(4) == 5);
}
