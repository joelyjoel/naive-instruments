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

TEST_CASE("Root mean square of a sample") {
  REQUIRE(Sample<int>({1, 1, 1, 1}).rms() == 1);
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

TEST_CASE("Slicing a sample") {
  Sample<int> master({0, 1, 2, 3, 4, 5, 6, 7, 8}, 1);
  auto slice = master.slice(2, 4);
  REQUIRE(slice->read(0) == 2);
  REQUIRE(slice->read(1) == 3);
}

TEST_CASE(
    "Reading between the samples, linear interpolation should be applied") {
  Sample<float> sample({0, 1, 2, 3});
  REQUIRE(sample.readWithInterpolation(0.0) == 0);
  REQUIRE(sample.readWithInterpolation(0.5) == .5);
  REQUIRE(sample.readWithInterpolation(3.0) == 3);
}

TEST_CASE("Selecting a single channel from a multichannel sample") {
  Sample<int> stereo({0, 1, 2, 3, 4, 5, 6}, 2);
  auto rightChannel = stereo.selectChannel(1);
  REQUIRE(rightChannel->read(0) == 1);
  REQUIRE(rightChannel->read(1) == 3);
  REQUIRE(rightChannel->read(2) == 5);
}
