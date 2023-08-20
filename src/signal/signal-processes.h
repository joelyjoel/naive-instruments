#include "../core/MonoBuffer.h"
#include "./Signal.h"
#include <algorithm>
#include <vector>

namespace NaiveInstruments
{


/**
 * Unsigned sawtooth wave
 */
class USaw : public Signal<double>
{
public:
    SignalReader<double> frequency{ this };

    void init() override
    {
        output = 0;
    }

    void action() override
    {
        // TODO: At some point we need figure out the right way to handle sample rate
        output += frequency[t] / 44100;
        output = fmod( output, 1.0 );
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
    SignalReader<T> input1{ this };
    SignalReader<T> input2{ this };


    void action() override
    {
        this->output = this->input1[this->t] + this->input2[this->t];
    }
};

template <typename T>
class Subtract : public Signal<T>
{
public:
    SignalReader<T> a{ this };
    SignalReader<T> b{ this };

    void action() override
    {
        this->output = this->a[this->t] - this->b[this->t];
    }
};

class SignFlip : public Signal<double>
{
public:
    SignalReader<double> input{ this };


    void action()
    {
        output = -input[t];
    }
};

class Multiply : public Signal<double>
{
public:
    SignalReader<double> a{ this };
    SignalReader<double> b{ this };


    void action() override
    {
        output = a[t] * b[t];
    }
};

class Divide : public Signal<double>
{
public:
    SignalReader<double> numerator{ this };
    SignalReader<double> denominator{ this };


    void action() override
    {
        output = numerator[t] / denominator[t];
    }
};

class MonoToStereo : public StereoSignal
{
public:
    SignalReader<double> input{ this };

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
    SignalReader<T> input{ this };

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
    SignalReader<double> input{ this };

    void init() override
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
    SignalReader<double> input{ this };
    SignalReader<double> maximum{ this };

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

template <typename T>
class VectorSignal : public Signal<T>
{
public:
    std::shared_ptr<std::vector<T>> buffer;

    VectorSignal( std::shared_ptr<std::vector<T>> v )

    {
        buffer       = v;
        this->output = ( *buffer )[0];
    }

    void action() override
    {
        if ( this->t < buffer->size() )
            this->output = ( *buffer )[this->t];
    }
};

class Sampler : public Signal<double>
{
    // TODO: Refactor this class, its been lazily adapted from the old version

    // TODO: should this really be a c ptr?
    MonoBuffer* buffer;
    int         playhead = 0;

public:
    Sampler( MonoBuffer* sharedBuffer )
    {
        buffer = sharedBuffer;
    }

    void init() override
    {
        writeOutput();
    }

public:
    void action() override
    {
        ++playhead;
        writeOutput();
    }

private:
    void writeOutput()
    {
        if ( playhead < 0 )
        {
            output = 0;
        }
        else if ( playhead < buffer->numberOfFrames() )
            output = ( *buffer )[playhead];
        else
            output = 0;
    }
};

class Wavetable : public Signal<double>
{
public:
    // TODO: make it multi channel
    MonoBuffer* buffer;

    SignalReader<double> phase{ this };

    Wavetable( MonoBuffer* buffer )
    : buffer( buffer )

    {
    }

    void action() override
    {

        output = buffer->interpolate( phase[t] * double( buffer->numberOfSamples ) );
    }
};

template <typename T>
class Wait : public Signal<T>
{
public:
    int             waitTime;
    SignalReader<T> input{ this };

    Wait( int countdown )
    : waitTime( countdown )
    {
    }

    void action()
    {
        if ( this->t > waitTime )
            this->output = input[this->t - waitTime];
        else
        {
            this->output = input[0]; // ?
            // output = 0 ?
            // noop ?
            // Whats best?
        }
    }
};

template <typename T>
class Skip : public Signal<T>
{
public:
    int             skipTime;
    SignalReader<T> input{ this };

    Skip( int skipTime )
    : skipTime( skipTime )
    {
    }

    void action()
    {
        this->output = input[this->t + skipTime];
    }
};

template <typename T>
class Elapse : public Signal<T>
{
public:
    int             elapseTime;
    SignalReader<T> input{ this };

    Elapse( int elapseTime )
    : elapseTime( elapseTime )
    {
    }

    void action() override
    {
        if ( this->t < elapseTime )
            this->output = input[this->t];
    }
};

class IntervalToRatio : public Signal<double>
{
public:
    SignalReader<double> interval{ this };


    void action() override
    {
        output = pow( 2.0, interval[t] / 12.0 );
    }
};


class BufferLooper : public Signal<double>
{
public:
    std::vector<double> buffer;

    SignalReader<double> input{ this };

    BufferLooper( int durationInSamples )
    : buffer( durationInSamples )
    {
    }

    void action() override
    {
        if ( t < buffer.size() )
            buffer[t] = input[t];
        output = buffer[t % buffer.size()];
    }
};

template <typename T>
class HardClip : public Signal<T>
{
public:
    SignalReader<T> input{ this };

    void action() override
    {
        // FIXME: Repeatedly using [] operator does cause some overhead (syncing input every time)
        this->output = clip( input[this->t] );
    }

    static double clip( double input )
    {
        if ( input > 1.0 )
            return 1.0;
        if ( input < -1.0 )
            return -1.0;
        else
            return input;
    }

    static StereoFrame clip( StereoFrame input )
    {
        return { clip( input.left ), clip( input.right ) };
    }
};

class LinearRamp : public Signal<double>
{
public:
    SignalReader<double> before{ this }, duration{ this }, after{ this };

    float phase = 0;

    void init() override
    {
        output = before[t] * ( 1 - phase ) + after[t] * phase;
    }

    void action() override
    {
        phase  = std::clamp( phase + 1.0 / ( duration[t] * 44100 ), 0.0, 1.0 );
        output = before[t] * ( 1 - phase ) + after[t] * phase;
    }
};

class ButterworthFilter : public Signal<double>
{
    void action() override
    {
        double x = input[t];
        calculateCoefficients( frequency[t], bandwidth[t] );

        y = a0 * x + a1 * x1 + a2 * x2 - b1 * y1 - b2 * y2;

        y2 = y1;
        y1 = y;
        x2 = x1;
        x1 = x;

        output = y;
    }

public:
    typedef enum
    {
        LowPass,
        HighPass,
        BandPass,
        BandReduce
    } FilterKind;

    FilterKind kind = LowPass;

    SignalReader<double> input{ this };
    SignalReader<double> frequency{ this };
    SignalReader<double> bandwidth{ this };

private:
    // Delays
    double x1 = 0, x2 = 0, y = 0, y1 = 0, y2 = 0;

    /// coefficients
    double a0, a1, a2, b1, b2;

    void calculateCoefficients( double frequency, double bandwidth )
    {

        double lamda, lamdaSquared, phi;
        switch ( kind )
        {

            case LowPass:
                lamda        = 1.0 / std::tan( M_PI * frequency / sampleRate );
                lamdaSquared = lamda * lamda;
                a0           = 1.0 / ( 1.0 + 2.0 * lamda + lamdaSquared );
                a1           = 2.0 * a0;
                a2           = a0;
                b1           = 2.0 * a0 * ( 1.0 - lamdaSquared );
                b2           = a0 * ( 1.0 - 2.0 * lamda + lamdaSquared );
                break;

            case HighPass:
                lamda        = std::tan( M_PI * frequency / sampleRate );
                lamdaSquared = lamda * lamda;
                a0           = 1 / ( 1 + 2 * lamda + lamdaSquared );
                a1           = 2 * a0;
                a2           = a0;
                b1           = 2 * a0 * ( lamdaSquared - 1 );
                b2           = a0 * ( 1 - 2 * lamda + lamdaSquared );
                break;

            case BandPass:
                lamda = 1 / std::tan( M_PI * bandwidth / sampleRate );
                phi   = 2 * std::cos( 2 * M_PI * frequency / sampleRate );
                a0    = 1 / ( 1 + lamda );
                a1    = 0;
                a2    = -a0;
                b1    = -lamda * phi * a0;
                b2    = a0 * ( lamda - 1 );
                break;

            case BandReduce:
                // TODO: Possibly buggy
                lamda = std::tan( M_PI * bandwidth / sampleRate );
                phi   = 2 * std::cos( 2 * M_PI * frequency / sampleRate );
                a0    = 1 / ( 1 + lamda );
                a1    = -phi * a0;
                a2    = a0;
                b1    = -phi * a0;
                b2    = a0 * ( lamda - 1 );
                break;
        }
    }
};


// TODO: Clamp
// TODO: Min
// TODO: Max
// TODO: Pace
// TODO: Pipe delay
// TODO: LinearRamp
// TODO: LinearDecay
// TODO: Decay using half life
// TODO: FadeIn
// TODO: FadeOut ? not sure how this one will work?


} // namespace NaiveInstruments
