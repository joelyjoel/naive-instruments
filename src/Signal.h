#pragma once

#include <cmath>
#include <iostream>
#include <memory>

namespace NaiveInstruments
{

class UnknownOutputSignal
{
public:
    typedef int    frame_position;
    frame_position t = 0;

    virtual void action()
    {
        // This must remain no-op on base class for constant signals to work.
    }

    void sync( frame_position until )
    {
        while ( t < until )
        {
            ++t;
            action();
        }
    }
};

template <typename T>
class Signal : public UnknownOutputSignal
{
    // For now everything is public
public:
    /// write signal output data to this
    T output;
};


// NOTE: Define constants before readers for handy operator overload for assigning constants to readers


template <typename T>
class SignalReader
{
public:
    std::shared_ptr<Signal<T>> ptr;


public:
    // Read a value by index from the signal
    T operator[]( UnknownOutputSignal::frame_position t )
    {
        ptr->sync( t );
        return ptr->output;
    }

    /// Assigning another signal to a signal reader
    void operator=( std::shared_ptr<Signal<T>> newSignal )
    {
        ptr = newSignal;
    }

    /// Assigning a constant to a signal reader
    void operator=( T constantValue )
    {

        std::shared_ptr<Signal<T>> newSignal = std::make_shared<Signal<T>>();
        newSignal->output                    = constantValue;
        ptr                                  = newSignal;
    }
};

// Mono and stereo typedefs:

typedef double                      MonoFrame;
typedef Signal<MonoFrame>           MonoSignal;
typedef SignalReader<MonoFrame>     MonoReader;
typedef std::shared_ptr<MonoSignal> MonoPtr, Mono;


struct StereoFrame
{
    double left, right;
};
typedef Signal<StereoFrame>           StereoSignal;
typedef SignalReader<StereoFrame>     StereoReader;
typedef std::shared_ptr<StereoSignal> StereoPtr, Stereo;


// Implementations:
const float sampleRate = 44100;


class Sawtooth : public MonoSignal
{
public:
    MonoReader frequency;
    double     phase;

    void action() override
    {
        phase += frequency[t] / sampleRate;
        output = phase * 2.0 - 1.0;
    }
};

/**
 * Add two signals together.
 *
 * Uses the `+` operator to define what adding signal frames means.
 */
template <typename T>
class Sum : public Signal<T>
{
public:
    SignalReader<T> input1;
    SignalReader<T> input2;

    void action() override
    {
        this->output = this->input1[this->t] + this->input2[this->t];
    }
};


class MonoToStereo : public StereoSignal
{
public:
    MonoReader input;

    void action() override
    {
        output.left  = input[t];
        output.right = input[t];
    };
};

template <typename T>
class Repeater : public Signal<T>
{
public:
    SignalReader<T> input;

    void action() override
    {
        this->output = input[this->t];
    }
};

/// signal that writes the frame position to the output field
template <typename T>
class Clock : public Signal<T>
{
public:
    Clock()
    {
        this->output = this->t;
    }
    void action() override
    {
        this->output = this->t;
    }
};

class Accumulator : public Signal<double>
{
public:
    SignalReader<double> input;

    Accumulator()
    {
        output = 0;
    }

    void action() override
    {
        output += input[t];
    }
};

class Modulo : public Signal<double>
{
public:
    SignalReader<double> input;
    SignalReader<double> maximum;

    void action() override
    {
        output = fmod( input[t], maximum[t] );
    }
};

} // namespace NaiveInstruments
