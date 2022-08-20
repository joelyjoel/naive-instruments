#include "../core.h"

class Invert : public Signal<double> {
public:
  SignalInput<double> &input = addInput<double>();

protected:
  void action() override { out(-input()); }
};
