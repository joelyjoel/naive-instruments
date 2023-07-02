#include "Signal.h"

namespace NaiveInstruments
{


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

class Noise : public Signal<double>
{
    Random random;

public:
    Noise( u_int64_t seed = 1 )
    : random( seed )
    {
        output = random.number( -1.0, 1.0 );
    }

    void action() override
    {
        output = random.number( -1.0, 1.0 );
    }
};

} // namespace NaiveInstruments
