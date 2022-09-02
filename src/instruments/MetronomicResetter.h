#include "../core.h"
#include "Metronome.h"
#include "Resetter.h"

class MetronomicResetter : public Patch<double> {
private:
  shared_ptr<Metronome> metronome = make_shared<Metronome>();
  shared_ptr<Resetter> resetter = make_shared<Resetter>();

public:
  SignalInput<double> &input = exposeInput(resetter->input);
  SignalInput<double> &bpm = exposeInput(metronome->bpm);

  MetronomicResetter() {
    resetter->trigger << metronome;
    exposeOutput(resetter);
  }

  std::string label() override { return "MetronomicResetter"; }
};
