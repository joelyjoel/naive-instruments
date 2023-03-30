
#include "AbstractFrameStreamConsumer.h"

/**
 * Abstraction for the inputs to a Signal
 */
template <typename frame>
class FrameStreamConsumer : public AbstractFrameStreamConsumer {

private:
public:
  FrameStreamConsumer(AbstractFrameStream *owner, const std::string &name,
                      bool keepSyncedToOwner = true)
      : AbstractFrameStreamConsumer(owner, name, keepSyncedToOwner) {
    setConstant(0);
  }

public:
  std::shared_ptr<FrameStream<frame>> typedConnection() {
    // Hmm seems risky
    return std::dynamic_pointer_cast<FrameStream<frame>>(untypedConnection);
  }

public:
  frame readFrame() {
    checkConnection();
    return typedConnection()->readFrame();
  }

  void connect(std::shared_ptr<FrameStream<frame>> inputSignal) {
    untypedConnection = inputSignal;
  }

public:
  void setConstant(frame k);

  FrameStream<frame> &
  operator<<(std::shared_ptr<FrameStream<frame>> instrument) {
    connect(instrument);
    return *instrument;
  }

  void operator<<(double k) { setConstant(k); }

  short numberOfChannels() { return typedConnection().numberOfChannels(); }
};
