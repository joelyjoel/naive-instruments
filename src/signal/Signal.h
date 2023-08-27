#pragma once

#include "../generative/Random.h"
#include "./ManagedSetter.h"
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
    frame_position t = -1;

    std::vector<AbstractManagedAccessor*> inputs;

    /**
     * Override this method to initialise state for your signal.
     * NOTE: State includes the output field.
     *
     * The default behavior is to call `action()` so only stateful signals
     * (those which update state besides the output field) need to override
     * this method.
     */
    virtual void init()
    {
        action();
    }

    /**
     * Override this method to update state from one frame to the next.
     * NOTE: State includes the output field.
     */
    virtual void action() = 0;

    virtual void sync( frame_position until )
    {
        if ( t == -1 || until < t )
        {
            t = 0;
            init();
        }
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
class Constant : public Signal<T>
{
public:
    void sync( UnknownOutputSignal::frame_position until ) override
    {
        this->t = until;
    }

    void action() override
    {
        // no-op, output should be set by the user of this class
    }
};


template <typename T>
class SignalReader : public ManagedAccessor<std::shared_ptr<Signal<T>>>
{

private:
    std::shared_ptr<Signal<T>> ptr;

public:
    SignalReader( UnknownOutputSignal* owner = nullptr )
    : ManagedAccessor<std::shared_ptr<Signal<T>>>( ptr )
    {
        if ( owner )
            owner->inputs.push_back( this );
    }

    // Read a value by index from the signal
    T operator[]( UnknownOutputSignal::frame_position t )
    {
        this->resource->sync( t );
        return this->ptr->output;
    }

    /// Assigning another signal to a signal reader
    void operator=( std::shared_ptr<Signal<T>> newSignal )
    {
        this->assign_manually( newSignal );
    }

    /// Assigning a constant to a signal reader
    void operator=( T constantValue )
    {
        std::shared_ptr<Signal<T>> newSignal = std::make_shared<Constant<T>>();
        newSignal->output                    = constantValue;
        this->assign_manually( newSignal );
    }

    std::shared_ptr<UnknownOutputSignal> get_signal() override
    {
        return ptr;
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
