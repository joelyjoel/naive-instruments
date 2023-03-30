#include "AbstractFrameStream.h"

template <typename frame> class FrameStream : public AbstractFrameStream {
protected:
  frame *output;

public:
  FrameStream() { allocateOutputFrame(); }
  ~FrameStream() { deallocateOutputFrame(); }

private:
  /**
   * Allocates heap memory used for writing ouptut frames.
   */
  void allocateOutputFrame() { output = new frame; };

  /**
   * Releases heap memory used for writing to the output.
   */
  void deallocateOutputFrame() { delete output; };

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
