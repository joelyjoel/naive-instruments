#include "../core.h"

class Noise : public Signal<double> {
  Random random;

public:
  Noise(uint64_t seed = 1) : random(seed) {}

private:
  double tick() { return random.number(-1, 1); }
};
