#include "../core.h"
#include "Metronome.h"
#include "Resetter.h"

class MetronomicResetter : public Patch<double> {
private:
  Metronome metronome;
  Resetter resetter;

public:
  SignalInput<double> &input = exposeInput(resetter.input);
  SignalInput<double> &bpm = exposeInput(metronome.bpm);

  MetronomicResetter() : Patch(resetter) { resetter.trigger << metronome; }

  std::string label() override { return "MetronomicResetter"; }
};
