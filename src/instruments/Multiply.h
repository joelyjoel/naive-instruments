#pragma once

#include "../core.h"

class Multiply : public FrameStream<double> {
public:
  FrameStreamConsumer<double> a{this, "a"};
  FrameStreamConsumer<double> b{this, "a"};

protected:
  void action() override { writeFrame(a.readFrame() * b.readFrame()); }

public:
  std::string label() override { return "Multiply"; }

  static shared_ptr<Multiply> create() { return make_shared<Multiply>(); }
};

/**
 * Mix an additional signal into a input
 */
void operator*=(FrameStreamConsumer<double> &signalInput,
                shared_ptr<FrameStream<double>> additionalSignal);

shared_ptr<FrameStream<double>> operator*(shared_ptr<FrameStream<double>> a,
                                          shared_ptr<FrameStream<double>> b);
