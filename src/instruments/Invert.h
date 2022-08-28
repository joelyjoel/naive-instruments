#include "../core.h"

class Invert : public Signal<double> {
public:
  SignalInput<double> &input = addInput<double>("input");

protected:
  void action() override { out(-input()); }
};
