#include "../core.h"
#include <cmath>

class ButterworthFilter : public Signal<double> {

  double x1 = 0, x2 = 0, y = 0, y1 = 0, y2 = 0;
  void action() override {
    double x = input();
    calculateCoefficients();

    y = a0 * x + a1 * x1 + a2 * x2 - b1 * y1 - b2 * y2;

    y2 = y1;
    y1 = y;
    x2 = x1;
    x1 = x;

    out(y);
  }

public:
  typedef enum { LowPass, HighPass, BandPass, BandReduce } FilterKind;

public:
  FilterKind kind = LowPass;

public:
  SignalInput<double> input = addInput<double>("input/audio");
  SignalInput<double> frequency = addInput<double>("frequency/Hz");
  SignalInput<double> bandwidth = addInput<double>("bandwidth/Hz");

private:
  double a0, a1, a2, b1, b2;
  void calculateCoefficients() {

    double lamda, lamdaSquared, phi;
    switch (kind) {

    case LowPass:
      lamda = 1.0 / std::tan(M_PI * frequency() / sampleRate);
      lamdaSquared = lamda * lamda;
      a0 = 1.0 / (1.0 + 2.0 * lamda + lamdaSquared);
      a1 = 2.0 * a0;
      a2 = a0;
      b1 = 2.0 * a0 * (1.0 - lamdaSquared);
      b2 = a0 * (1.0 - 2.0 * lamda + lamdaSquared);
      break;

    case HighPass:
      lamda = std::tan(M_PI * frequency() / sampleRate);
      lamdaSquared = lamda * lamda;
      a0 = 1 / (1 + 2 * lamda + lamdaSquared);
      a1 = 2 * a0;
      a2 = a0;
      b1 = 2 * a0 * (lamdaSquared - 1);
      b2 = a0 * (1 - 2 * lamda + lamdaSquared);
      break;

    case BandPass:
      lamda = 1 / std::tan(M_PI * bandwidth() / sampleRate);
      phi = 2 * std::cos(2 * M_PI * frequency() / sampleRate);
      a0 = 1 / (1 + lamda);
      a1 = 0;
      a2 = -a0;
      b1 = -lamda * phi * a0;
      b2 = a0 * (lamda - 1);
      break;

    case BandReduce:
      // TODO: Possibly buggy
      lamda = std::tan(M_PI * bandwidth() / sampleRate);
      phi = 2 * std::cos(2 * M_PI * frequency() / sampleRate);
      a0 = 1 / (1 + lamda);
      a1 = -phi * a0;
      a2 = a0;
      b1 = -phi * a0;
      b2 = a0 * (lamda - 1);
      break;
    }
  }
};
