#include <cstdlib>
#include <iostream>
#include <string>

class Random {

private:
  const long seed;
  long latest;

public:
  Random(long seed = 1) : seed(seed) {
    if (seed == 0) {
      std::cerr << "Random seed may not be 0\n";
      throw 1;
    }
    latest = seed;
  }

  long next() {
    latest ^= (latest << 21);
    latest ^= (latest >> 35);
    latest ^= (latest << 4);
    return latest;
  }

public:
  float number() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }

  float number(float max) { return number() * max; }
  float number(float min, float max) { return number() * (max - min) + min; }

  float frequency(float min = 20, float max = 20000) {
    return number(min, max);
  }

  float pitch(float min = 21, float max = 108) { return number(min, max); }
};
