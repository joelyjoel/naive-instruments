#pragma once

#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

using std::shared_ptr, std::make_shared;

#include "AbstractFrameStream.h"

template <typename frame> class FrameStream : public AbstractFrameStream {
protected:
  frame *output;

public:
  FrameStream() { output = new frame; }
  ~FrameStream() { delete output; }

protected:
  /**
   * Update the latest frame.
   */
  void writeFrame(const frame &y) { *output = y; }

public:
  frame operator[](int clock) {
    sync(clock);
    return readFrame();
  }

  frame readFrame() { return *output; }

  frame advanceToNextFrameAndRead() {
    advanceToNextFrame();
    return readFrame();
  }

  AbstractFrameStreamConsumer &defaultInput() {
    if (inputs.size() > 0)
      return *inputs[0];
    else {
      std::cerr << "Trying to get default input but the Signal has no inputs";
      throw 1;
    }
  }

  void operator<<(double k) { defaultInput().setConstant(k); }

public:
  std::string summary() override {
    return label() + "[" + std::to_string(internalClock) +
           "] = " + std::to_string(*output);
  }
};

/**
 * Convenient alias for very freqeuent type.
 */
typedef shared_ptr<FrameStream<double>> sigarette;
