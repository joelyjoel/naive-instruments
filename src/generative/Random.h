#pragma once

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

class Random {

public:
  static uint64_t clockSeed() {
    uint64_t seed = time(NULL);

    for (int i = 0; i < 10; ++i)
      seed = xorshift(seed);
    return seed;
  }

private:
  static uint64_t xorshift(uint64_t x) {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
  }

private:
  const uint64_t seed;
  uint64_t latest;

public:
  Random(uint64_t seed = clockSeed()) : seed(seed) {
    if (seed == 0) {
      std::cerr << "Random seed may not be 0\n";
      throw 1;
    }
    latest = seed;
  }

  uint64_t next() {
    latest = xorshift(latest);
    return latest;
  }

public:
  float number() {
    return static_cast<float>(next()) /
           static_cast<float>(std::numeric_limits<uint64_t>::max());
  }
  uint64_t operator()() { return number(); }

  float number(float max) { return number() * max; }
  float operator()(float max) { return number(max); }

  float number(float min, float max) { return number() * (max - min) + min; }
  float operator()(float min, float max) { return number(min, max); }

  float frequency(float min = 20, float max = 20000) {
    return number(min, max);
  }

  float pitch(float min = 21, float max = 108) { return number(min, max); }
};
