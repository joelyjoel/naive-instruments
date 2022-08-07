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
protected:
  const UntypedSignal *owner;
  UntypedSignal *currentConnection = nullptr;

public:
  UntypedSignalInput(UntypedSignal *owner, const string &name) : owner(owner) {}

  bool hasConnection() { return currentConnection != nullptr; }
  UntypedSignal &untypedConnection() { return *currentConnection; }

  void sync(int clock);
};

template <typename frame> class SignalInput : public UntypedSignalInput {
private:
  frame constant;

public:
  SignalInput(UntypedSignal *owner, const string &name = "unlabelled")
      : UntypedSignalInput(owner, name) {}

  frame operator()() {
    if (hasConnection())
      return connection()();
    else
      return constant;
  }

  void connect(Signal<frame> *signal) { currentConnection = signal; }
  void setConstant(frame k) {
    currentConnection = nullptr;
    constant = k;
  }
  frame getConstant() { return constant; }

public:
  Signal<frame> &connection() { return *currentConnection; }
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
  template <typename T>
  SignalInput<T> &addInput(const string &name = "unlabelled_input") {
    SignalInput<T> *input = new SignalInput<T>(this, name);
    inputs.push_back(input);
    return *input;
  }

  /**
   * Sometimes you just want to add a pointer to an existing input so that it is
   * syncronised along with the others.
   */
  void addInput(UntypedSignalInput *input) { inputs.push_back(input); }

public:
  UntypedSignalInput &defaultInput() { return *inputs[0]; }

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

public:
  void reset() {
    // FIXME: Circuit breaker for feedback loops
    for (auto input : inputs)
      if (input->hasConnection())
        input->untypedConnection().reset();

    resetState();
  }

protected:
  /**
   * Stateful signals can override this method to reset their state.
   */
  virtual void resetState() {
    // noop
  }
};

template <typename frame> class Signal : public UntypedSignal {
private:
  frame latestFrame;

public:
  frame operator()() { return latestFrame; }
  frame operator[](int clock) {
    sync(clock);
    return latestFrame;
  }
  frame operator++() {
    sync(internalClock + 1);
    return latestFrame;
  }

protected:
  void out(const frame &y) { latestFrame = y; }
};

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> &a, Signal<frame> &b);

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> *a, Signal<frame> &b);

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> &a, Signal<frame> *b);

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> *a, Signal<frame> *b);

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> &a, frame b);

template <typename frame>
Signal<frame> &operator<<(SignalInput<frame> *a, frame b);
