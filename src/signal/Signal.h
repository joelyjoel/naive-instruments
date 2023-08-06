#pragma once

#include "../generative/Random.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>


namespace NaiveInstruments
{


class AbstractSignalReader;


class UnknownOutputSignal
{
public:
    typedef int    frame_position;
    frame_position t = 0;

    std::vector<AbstractSignalReader*> inputs;

    virtual void action() = 0;

    void sync( frame_position until )
    {
        while ( t < until )
        {
            ++t;
            action();
        }
    }
};

class AbstractSignalReader
{
public:
    AbstractSignalReader( UnknownOutputSignal* owner = nullptr )
    {
        if ( owner )
            owner->inputs.push_back( this );
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
class Constant : public Signal<T>
{
    void action() override
    {
        // no-op, you just set the output directly
    }
};


template <typename T>
class SignalReader : public AbstractSignalReader
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

        std::shared_ptr<Signal<T>> newSignal = std::make_shared<Constant<T>>();
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
} // namespace NaiveInstruments
