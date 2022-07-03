#pragma once

#include "../parsing/Parse.h"
#include "../parsing/RegularExpressionSources.h"
#include "BreakpointEnvelope.h"
#include <iostream>
#include <regex>
#include <string>

using std::string, std::regex, std::smatch, std::regex_match, std::vector;

class ControlSignal : public BreakpointEnvelope {
public:
  bool appendControlString(const string &controlStr) {
    const string patternSrc =
        "^" + RegularExpressionSources::controlSequence + "$";
    std::cerr << "Pattern src: '" << patternSrc << "'\n";
    const regex pattern(patternSrc);
    smatch instructionStrings;
    if (regex_match(controlStr, instructionStrings, pattern)) {
      std::cerr << "Found " << instructionStrings.size()
                << " instructions within '" << controlStr << "'\n";
      for (int i = 1; i < instructionStrings.size(); ++i)
        appendInstructionString(instructionStrings[i].str());
      flushInterpolation();
      return true;
    } else {
      return false;
    }
  }

  void operator+=(const string &instructions) {
    appendControlString(instructions);
  }

  ControlSignal() {}

  static Hopefully<ControlSignal *> parse(const string &instructions) {
    auto instance = new ControlSignal();
    if (instance->appendControlString(instructions))
      return instance;
    else {
      delete instance;
      return Disappointment;
    }
  }

private:
  bool appendInstructionString(const string &instruction) {
    std::cerr << "Appending instruction '" << instruction << "'\n";
    return appendTempoInstruction(instruction) ||
           appendValueInstruction(instruction) ||
           appendSustainInstruction(instruction);
  }

  float stepInterval = 1;
  bool appendTempoInstruction(const string &instruction) {
    std::cerr << "Attempting to append tempo instruction\n";
    if (instruction.ends_with(':')) {
      const Hopefully<float> interval =
          Parse::interval(instruction.substr(0, -1));
      if (interval.success()) {
        stepInterval = *interval;
        return true;
      } else
        return false;
    }
    return false;
  }

  bool appendValueInstruction(const string &instruction) {
    std::cerr << "Attempting to append value instructiont \n";
    // TODO: Use dynamic domain parsing
    const Hopefully<float> y = Parse::frequency(instruction);
    if (y.success()) {
      flushInterpolation(*y);
      return true;
    } else
      return false;
  }

  typedef enum { Rest = 0, LinearGlide } InterpolationStrategy;
  typedef struct {
    float duration;
    InterpolationStrategy interpolationStrategy;
  } InterpolationStep;

  vector<InterpolationStep> interpolationSteps;

  bool appendSustainInstruction(const string &instruction) {
    std::cerr << "Attempting to append sustain instruction\n";
    regex pattern(RegularExpressionSources::controlSequenceSustainInstruction);
    if (!regex_match(instruction, pattern))
      return false;
    else {
      for (int i = 0; i < instruction.size(); ++i) {
        char c = instruction[i];
        if (c == '_')
          interpolationSteps.push_back({stepInterval, Rest});
        else if (c == '~')
          interpolationSteps.push_back({stepInterval, LinearGlide});
        else if (c == ' ')
          continue;
        else {
          std::cerr << "Unexpected character in sustain instruction: " << c
                    << "\n";
          throw 1;
        }
      }
      return true;
    }
  }

  int sumGlidingDuration() {
    float duration = 0;
    for (auto &step : interpolationSteps)
      if (step.interpolationStrategy == LinearGlide)
        duration += step.duration;
    return duration;
  }

  void flushInterpolation(float nextValue) {
    const float previousValue = lastEndValue();
    const float glidingDuration = sumGlidingDuration();
    const float distance = nextValue - previousValue;
    const float gradient = distance / glidingDuration;

    float y = previousValue;
    for (auto step : interpolationSteps) {
      if (step.interpolationStrategy == Rest)
        addSection(y, y, step.duration);
      else if (step.interpolationStrategy == LinearGlide) {
        const float endValue = y + gradient * step.duration;
        addSection(y, endValue, step.duration);
        y = endValue;
      } else
        throw 1;
    }
  }

  void flushInterpolation() { flushInterpolation(lastEndValue()); }
};
