#pragma once

#include "../core.h"

class IntervalToRatio : public FrameStream<double> {
public:
  SignalInput<double> interval{this, "interval/st"};

  static shared_ptr<IntervalToRatio> create() {
    return make_shared<IntervalToRatio>();
  }

  std::string label() override { return "IntervalToRatio"; }

protected:
  void action() override { out(pow(2.0, (interval() / 12.0))); }
};

shared_ptr<IntervalToRatio>
intervalToRatio(shared_ptr<FrameStream<double>> intervalSignal) {
  auto converter = IntervalToRatio::create();
  converter->interval << intervalSignal;
  return converter;
}

class PitchConverter : public FrameStream<double> {
public:
  SignalInput<double> pitch{this, "pitch/MIDI"};

  static shared_ptr<PitchConverter> create() {
    return make_shared<PitchConverter>();
  }

  std::string label() override { return "PitchConverter"; }

private:
  void action() override { out(440 * pow(2.0, ((pitch() - 69) / 12.0))); }
};

shared_ptr<PitchConverter>
pitchToFrequency(shared_ptr<FrameStream<double>> pitchSignal) {
  auto converter = PitchConverter::create();
  converter->pitch << pitchSignal;
  return converter;
}
