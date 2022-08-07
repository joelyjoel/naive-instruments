#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::cerr;
using std::string, std::vector;

// Forward declarations
template <typename frame> class Signal;
template <typename frame> class SignalInput;
class UntypedSignal;
class UntypedSignalInput;

class UntypedSignalInput {
private:
  const UntypedSignal *owner;
  UntypedSignal *currentConnection = nullptr;

public:
  UntypedSignalInput(UntypedSignal *owner, const string &name) : owner(owner) {}
  bool hasConnection() { return currentConnection != nullptr; }
  UntypedSignal &connection() { return *currentConnection; }

  void sync(int clock);
};

template <typename frame> class SignalInput : UntypedSignalInput {
private:
  frame constant;

public:
  frame operator()() {
    if (hasConnection())
      return connection().latestFrame;
    else
      return constant;
  }
};

class UntypedSignal {
protected:
  /**
   * Override the behaviour of this method to define the behaviour of the new
   * kinds of Signal.
   */
  virtual void action() {
    cerr << "Looks like the programmer forgot to override the "
            "UntypedSignal::action() method!\n";
  }

protected:
  vector<UntypedSignalInput *> inputs;
  template <typename T> SignalInput<T> &addInput(const string &name) {
    SignalInput<T> *input = new SignalInput<T>(this, name);
    inputs.push_back(input);
    return *input;
  }

private:
  void syncInputs() {
    for (auto input : inputs)
      input->sync(internalClock);
  }

protected:
  int internalClock = 0;

public:
  void sync(int clock) {
    while (internalClock < clock) {
      ++internalClock;
      syncInputs();
      action();
    }
  }
};

template <typename frame> class Signal : public UntypedSignal {
private:
  frame latestFrame;

public:
  frame operator()() { return latestFrame; }

protected:
  void out(frame &y) { latestFrame = y; }
};
