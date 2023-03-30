#include "AbstractFrameStream.h"

template <typename frame> class FrameStream : public AbstractFrameStream {
protected:
  frame *output;
  short numberOfOutputChannels;

public:
  FrameStream(short numberOfChannels = 1) {
    numberOfOutputChannels = numberOfChannels;
    allocateOutputFrame(numberOfChannels);
  }
  ~FrameStream() { deallocateOutputFrame(); }

private:
  /**
   * Allocates heap memory used for writing ouptut frames.
   */
  void allocateOutputFrame(short numberOfChannels) {
    output = new frame[numberOfChannels];
  };

  /**
   * Releases heap memory used for writing to the output.
   */
  void deallocateOutputFrame() {
    // QUESTION: ask a cpp expert, is it ok that I'm not telling it how long the
    // array is?
    delete output;
  };

protected:
  /**
   * Changes the number of ouptut channels.
   */
  void resizeOutputChannels(short numberOfChannels) {
    deallocateOutputFrame();
    numberOfOutputChannels = numberOfChannels;
    allocateOutputFrame(numberOfChannels);
  }

public:
  short numberOfChannels() { return numberOfOutputChannels; };

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
