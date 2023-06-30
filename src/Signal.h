#include <iostream>
#include <memory>


class UnknownOutputSignal
{
public:
    typedef int    frame_position;
    frame_position t = 0;

    virtual void action()
    {
        // This must remain no-op for constant signals to work!
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
private:
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
        auto k = std::make_shared<Signal<T>>( constantValue );
        // FIXME: This part I've not tested...
        ptr = std::static_pointer_cast<Signal<T>>( k );
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

// TODO: Use a template for Add
class Add : public MonoSignal
{
public:
    MonoReader a;
    MonoReader b;

    void action() override
    {
        output = a[t] + b[t];
    }
};

class StereoAdd : public StereoSignal
{
public:
    StereoReader a;
    StereoReader b;

    void action() override
    {
        // TODO: Coulde be optimised in a couple of ways to reduce risk and processing
        output.left  = a[t].left + b[t].left;
        output.right = a[t].right + b[t].right;
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
