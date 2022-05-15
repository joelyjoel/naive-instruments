#pragma once

#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

#define YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE 420
#define CANT_ACCESS_SIGNAL_FROM_THE_PAST_ERROR_CODE 69

class AbstractSocket;
template <typename SignalFrame> class Socket;

/**
 * This class just exists so that sockets don't have to know the SignalFrame
 * type of their owners.
 */
class UntypedInstrument {
public:
  int internalClock = 0;

protected:
  std::vector<AbstractSocket *> sockets;

protected:
  template <typename SignalFrame>
  Socket<SignalFrame> &addSocket(double initValue = 0) {
    auto socket = new Socket<SignalFrame>(this);
    sockets.push_back(socket);
    return *socket;
  }

public:
  virtual std::string label() { return "NaiveInstrument"; }
  std::string summary() {
    return label() + "@" + std::to_string(internalClock);
  }
};

/**
 * I think its intuitive to think of audio processes like little machines.
 */
template <typename SignalFrame>
class NaiveInstrument : public UntypedInstrument {
protected:
  SignalFrame latestFrame;

public:
  SignalFrame tickUntil(int time) {
    while (internalClock < time) {
      ++internalClock;
      latestFrame = tick();
    }
    if (time > internalClock)
      throw CANT_ACCESS_SIGNAL_FROM_THE_PAST_ERROR_CODE;
    return latestFrame;
  }

  /**
   * Naive instruments work a bit like clock work. Every frame of the digital
   * signal they "tick". What they actually do when they tick is up to them!
   */
  virtual SignalFrame tick() {
    throw YOU_MUST_IMPLEMENT_THIS_YOURSELF_ERROR_CODE;
  }

  SignalFrame operator[](int index) { return tickUntil(index); }

  SignalFrame next() { return tickUntil(internalClock + 1); }
  SignalFrame operator++() { return next(); }

  template <typename InputSignalFrame>
  void operator<<(NaiveInstrument<InputSignalFrame> &signal) {
    sockets[0]->connect(&signal);
  }

  void operator<<(double k) { sockets[0]->setConstant(k); }
};
