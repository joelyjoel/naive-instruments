#pragma once

#include "../parsing/LazyRegex.h"
#include "../parsing/NumberWithUnit.h"
#include "./BreakpointEnvelope.h"
#include <string>

using std::string;

class ControlString : public BreakpointEnvelope {

public:
  class TempoInstruction {
  public:
    static LazyRegex pattern;

    static Hopefully<float> parse(const string &str) {
      if (pattern.test(str)) {
        return NumberWithUnit::parseInterval(str.substr(0, str.size() - 1));
      } else
        return Disappointment;
    }
  };

  class ValueInstruction {
  public:
    static LazyRegex pattern;

    static Hopefully<float> parse(const string &str) {
      if (pattern.test(str)) {
        auto nu = NumberWithUnit::parse(str);
        // TODO: Clearly this needs work
        if (nu.success() && nu->unit == Units::noUnit)
          return nu->number;
        else
          return Disappointment;

      } else
        return Disappointment;
    }
  };

  class SustainStepInstruction {
  public:
    static LazyRegex pattern;

    typedef enum { Resting, Gliding } SustainKind;

    static Hopefully<SustainKind> parse(const string &str) {
      if (str == "~")
        return Gliding;
      else if (str == "_")
        return Resting;
      else
        return Disappointment;
    }
  };

  bool append(const string &str) {
    std::smatch result;
    string remainder = str.substr(0, str.size());
    while (std::regex_search(remainder, result, *firstInstructionPattern)) {
      appendInstruction(result[1]);
      remainder = remainder.substr(result[0].str().size(), remainder.size());
    }

    if (remainder.size() == 0)
      return true;
    else
      return false;
  }

  /**
   * returns `true` when successful.
   */
  bool appendInstruction(const string &str) {
    auto sustainInstruction = SustainStepInstruction::parse(str);
    if (sustainInstruction.success())
      return appendSustainInstruction(*sustainInstruction);

    auto tempoInstruction = TempoInstruction::parse(str);
    if (tempoInstruction.success()) {
      return appendTempoInstruction(*tempoInstruction);
    }

    auto value = ValueInstruction::parse(str);
    if (value.success()) {
      return appendValueInstruction(*value);
    }

    return false;
  }

private:
  struct SustainStep {
    double duration;
    SustainStepInstruction::SustainKind kind;
  };
  std::vector<SustainStep> sustainSteps;

  int countGlidingSteps() {
    int n = 0;
    for (auto &step : sustainSteps)
      if (step.kind == SustainStepInstruction::Gliding)
        ++n;
    return n;
  }

  double lastValue = lastEndValue();
  void flushSustainSteps(double target) {
    const int numberOfGlidingSteps = countGlidingSteps();
    double y = lastValue;
    const double totalChange = target - y;
    const double changePerGlidingStep = totalChange / numberOfGlidingSteps;
    for (auto &step : sustainSteps) {
      if (step.kind == SustainStepInstruction::Gliding) {
        addSection(y, y + changePerGlidingStep, step.duration);
        y += changePerGlidingStep;
      } else {
        addHold(step.duration);
      }
    }
    sustainSteps.clear();
  }

public:
  bool appendSustainInstruction(
      SustainStepInstruction::SustainKind sustainInstruction) {
    sustainSteps.push_back({stepInterval, sustainInstruction});
    return true;
  }

  float stepInterval = 1;
  bool appendTempoInstruction(float interval) {
    stepInterval = interval;
    return true;
  }

public:
  bool appendValueInstruction(float target) {
    if (sustainSteps.size() > 0)
      flushSustainSteps(target);
    else
      restValue = target;
    lastValue = target;
    return true;
  }

public:
  static LazyRegex anyInstructionPattern;
  static LazyRegex firstInstructionPattern;
  static LazyRegex pattern;

  static Hopefully<ControlString *> parse(const std::string &str) {
    ControlString *instance = new ControlString();
    auto successful = instance->append(str);
    if (!successful) {
      std::cerr << "Couldn't parse control string: \"" << str << "\"n";
      return Disappointment;
    }

    instance->flushSustainSteps(instance->restValue);

    return instance;
  }
};
