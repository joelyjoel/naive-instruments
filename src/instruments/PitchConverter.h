#pragma once

#include "../core.h"

class IntervalToRatio : public Signal<double> {
public:
  SignalInput<double> interval{this, "interval/st"};

  void action() { out(pow(2.0, (interval() / 12.0))); }
};

class PitchConverter : public Signal<double> {
public:
  SignalInput<double> pitch{this, "pitch/MIDI"};

  void action() override { out(440 * pow(2.0, ((pitch() - 69) / 12.0))); }

  std::string label() override { return "PitchConverter"; }
};
