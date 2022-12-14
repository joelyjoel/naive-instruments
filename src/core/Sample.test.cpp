#include "./Sample.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("reading and writing to a sample") {

  Sample<bool> mySample(8);
  mySample.write(true, 0, 0);
  REQUIRE(mySample.readByFrame(0, 0) == true);
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
  REQUIRE(master.readByFrame(1) == 2);
};

TEST_CASE("Overrwriting a region using another sample and an offset") {
  Sample<int> master(8);
  Sample<int> overdub({1, 2, 3, 4});
  master.write(overdub, 2);
  REQUIRE(master.readByFrame(1) == 0);
  REQUIRE(master.readByFrame(2) == 1);
  REQUIRE(master.readByFrame(5) == 4);
}

TEST_CASE("Concatenating two samples") {
  Sample<int> first({1, 2, 3, 4});
  Sample<int> second({5, 6, 7, 8});

  auto combined = Sample<int>::concat(first, second);
  REQUIRE(combined->readByFrame(7) == 8);
  REQUIRE(combined->readByFrame(0) == 1);
}

TEST_CASE("Concatenation using << operator") {
  Sample<int> first({1, 2, 3, 4});
  Sample<int> second({5, 6, 7, 8});
  auto combined = first << second;
  REQUIRE(combined->readByFrame(7) == 8);
  REQUIRE(combined->readByFrame(0) == 1);
}

TEST_CASE("Mixing two samples together using the overdub method") {
  Sample<int> master({1, 1, 1, 1, 1});
  Sample<int> overdub({0, 1, 2, 3, 4});

  master.overdub(overdub);

  REQUIRE(master.readByFrame(0) == 1);
  REQUIRE(master.readByFrame(1) == 2);
  REQUIRE(master.readByFrame(2) == 3);
  REQUIRE(master.readByFrame(3) == 4);
  REQUIRE(master.readByFrame(4) == 5);
}

TEST_CASE("Mixing a sample in place using the += operator") {
  Sample<int> master({1, 1, 1, 1, 1});
  Sample<int> overdub({0, 1, 2, 3, 4});

  master += overdub;

  REQUIRE(master.readByFrame(0) == 1);
  REQUIRE(master.readByFrame(1) == 2);
  REQUIRE(master.readByFrame(2) == 3);
  REQUIRE(master.readByFrame(3) == 4);
  REQUIRE(master.readByFrame(4) == 5);
}

TEST_CASE("Slicing a sample") {
  Sample<int> master({0, 1, 2, 3, 4, 5, 6, 7, 8}, 1);
  auto slice = master.slice(2, 4);
  REQUIRE(slice->readByFrame(0) == 2);
  REQUIRE(slice->readByFrame(1) == 3);
}

TEST_CASE(
    "Reading between the samples, linear interpolation should be applied") {
  Sample<float> sample({0, 1, 2, 3}, 1, 1);
  REQUIRE(sample.readWithInterpolation(0.0) == 0);
  REQUIRE(sample.readWithInterpolation(0.5) == .5);
  REQUIRE(sample.readWithInterpolation(3.0) == 3);
}

TEST_CASE("Selecting a single channel from a multichannel sample") {
  Sample<int> stereo({0, 1, 2, 3, 4, 5, 6}, 2);
  auto rightChannel = stereo.selectChannel(1);
  REQUIRE(rightChannel->readByFrame(0) == 1);
  REQUIRE(rightChannel->readByFrame(1) == 3);
  REQUIRE(rightChannel->readByFrame(2) == 5);
}

TEST_CASE("Stereo flip using selectChannels") {
  Sample<int> stereo({0, 1, 2, 3, 4, 5, 6}, 2);
  std::vector<int> channels = {1, 0};
  auto flipped = stereo.selectChannels(channels);
  REQUIRE(flipped->readByFrame(0) == 1);
  REQUIRE(flipped->readByFrame(0, 1) == 0);
  REQUIRE(flipped->readByFrame(1, 0) == 3);
  REQUIRE(flipped->readByFrame(1, 1) == 2);
}

TEST_CASE("Stereo flip using dedicated stereoFlip method") {
  Sample<int> stereo({0, 1, 2, 3, 4, 5, 6}, 2);
  auto flipped = stereo.stereoFlip();
  REQUIRE(flipped->readByFrame(0) == 1);
  REQUIRE(flipped->readByFrame(0, 1) == 0);
  REQUIRE(flipped->readByFrame(1, 0) == 3);
  REQUIRE(flipped->readByFrame(1, 1) == 2);
}

TEST_CASE("== operator for comparing samples, trivial example") {
  Sample<int> a({0, 1, 2, 3}), b({0, 1, 2, 3}), c({1, 1, 1, 1});
  REQUIRE((a == b) == true);
  REQUIRE((b == a) == true);
  REQUIRE((c != a) == true);
  REQUIRE((b != c) == true);
  REQUIRE((c != b) == true);
  REQUIRE((a != c) == true);
}

TEST_CASE("Looping a sample to twice its original duration") {
  Sample<int> original({1, 2, 3, 4});

  auto twice = original.loop(2);
  REQUIRE(twice->readByFrame(0) == 1);
  REQUIRE(twice->readByFrame(1) == 2);
  REQUIRE(twice->readByFrame(2) == 3);
  REQUIRE(twice->readByFrame(3) == 4);
  REQUIRE(twice->readByFrame(4) == 1);
  REQUIRE(twice->readByFrame(5) == 2);
  REQUIRE(twice->readByFrame(6) == 3);
  REQUIRE(twice->readByFrame(7) == 4);
  REQUIRE(twice->numberOfFrames() == 8);
}

TEST_CASE("Looping a sample to 1.5x its original duration") {
  Sample<int> original({1, 2, 3, 4});

  auto twice = original.loop(1.5);
  REQUIRE(twice->readByFrame(0) == 1);
  REQUIRE(twice->readByFrame(1) == 2);
  REQUIRE(twice->readByFrame(2) == 3);
  REQUIRE(twice->readByFrame(3) == 4);
  REQUIRE(twice->readByFrame(4) == 1);
  REQUIRE(twice->readByFrame(5) == 2);
  REQUIRE(twice->numberOfFrames() == 6);
}

TEST_CASE("Looping a sample to a specific duration (in frames)") {
  Sample<int> original({1, 2, 3, 4});
  auto twice = original.loopToFrames(6);
  REQUIRE(twice->readByFrame(0) == 1);
  REQUIRE(twice->readByFrame(1) == 2);
  REQUIRE(twice->readByFrame(2) == 3);
  REQUIRE(twice->readByFrame(3) == 4);
  REQUIRE(twice->readByFrame(4) == 1);
  REQUIRE(twice->readByFrame(5) == 2);
  REQUIRE(twice->numberOfFrames() == 6);
}

TEST_CASE("Loop to a duration specified in seconds") {
  Sample<int> original({1, 2, 3, 4}, 1, 44100);
  auto twice = original.loopToDuration(1);
  REQUIRE(twice->readByFrame(0) == 1);
  REQUIRE(twice->readByFrame(1) == 2);
  REQUIRE(twice->readByFrame(2) == 3);
  REQUIRE(twice->readByFrame(3) == 4);
  REQUIRE(twice->readByFrame(4) == 1);
  REQUIRE(twice->readByFrame(5) == 2);
  REQUIRE(twice->numberOfFrames() == 44100);
}

TEST_CASE("Converting a floating point sample into an integer one") {
  Sample<float> original({1.0, 2.0, 3.0, 4.0});
  auto converted = original.convertTo<int>();
  REQUIRE(original.readByFrame(0) == 1);
  REQUIRE(original.readByFrame(1) == 2);
  REQUIRE(original.readByFrame(2) == 3);
  REQUIRE(original.readByFrame(3) == 4);
}

TEST_CASE("can recognise metadata for a mono sample") {
  auto sample = Sample<float>::readFile("audio-source-files/Egg-Moww.wav");
  REQUIRE(sample->numberOfChannels() == 1);
  REQUIRE(sample->sampleRate == 44100);
}

TEST_CASE("Writing a sample, then reading it again") {
  Sample<float> original({1, 2, 3, 3});
  original.writeFile("test-outputs/test.wav");
  auto fromFile = Sample<float>::readFile("test-outputs/test.wav");
  REQUIRE(fromFile->readByFrame((0) == 1));
  REQUIRE(fromFile->readByFrame((1) == 2));
  REQUIRE(fromFile->readByFrame((2) == 3));
  REQUIRE(fromFile->readByFrame((3) == 4));
}

TEST_CASE("Writing a sample as floats, then reading it again as ints") {
  Sample<float> original({1, 2, 3, 3});
  original.writeFile("test-outputs/test.wav");
  auto fromFile = Sample<int>::readFile("test-outputs/test.wav");
  REQUIRE(fromFile->readByFrame((0) == 1));
  REQUIRE(fromFile->readByFrame((1) == 2));
  REQUIRE(fromFile->readByFrame((2) == 3));
  REQUIRE(fromFile->readByFrame((3) == 4));
}

TEST_CASE("Writing a sample as ints, reading it as floats") {
  Sample<int> original({1, 2, 3, 3});
  original.writeFile("test-outputs/test.wav");
  auto fromFile = Sample<float>::readFile("test-outputs/test.wav");
  REQUIRE(fromFile->readByFrame((0) == 1));
  REQUIRE(fromFile->readByFrame((1) == 2));
  REQUIRE(fromFile->readByFrame((2) == 3));
  REQUIRE(fromFile->readByFrame((3) == 4));
}

TEST_CASE("Writing a sample as floats, reading it as doubles") {
  Sample<float> original({1, 2, 3, 3});
  original.writeFile("test-outputs/test.wav");
  auto fromFile = Sample<double>::readFile("test-outputs/test.wav");
  REQUIRE(fromFile->readByFrame((0) == 1));
  REQUIRE(fromFile->readByFrame((1) == 2));
  REQUIRE(fromFile->readByFrame((2) == 3));
  REQUIRE(fromFile->readByFrame((3) == 4));
};
