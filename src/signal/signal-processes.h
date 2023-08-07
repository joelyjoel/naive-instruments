#include "../core/MonoBuffer.h"
#include "./Signal.h"
#include "./naming.h"
#include <algorithm>
#include <arm/types.h>
#include <vector>

namespace NaiveInstruments
{


/**
 * Unsigned sawtooth wave
 */
class USaw : public Signal<double>
{

public:
    use_name( "USaw" );

    SignalReaderWithName<"frequency", double> frequency{ this };

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
    use_name( "Sum" );
    SignalReaderWithName<"a", T> a{ this };
    SignalReaderWithName<"b", T> b{ this };


    void action() override
    {
        this->output = this->a[this->t] + this->b[this->t];
    }
};

template <typename T>
class Subtract : public Signal<T>
{

public:
    use_name( "Subtract" );

    SignalReaderWithName<"a", T> a{ this };
    SignalReaderWithName<"b", T> b{ this };

    void action() override
    {
        this->output = this->a[this->t] - this->b[this->t];
    }
};

class SignFlip : public Signal<double>
{

public:
    use_name( "SignFlip" );

    SignalReaderWithName<"input", double> input{ this };


    void action() override
    {
        output = -input[t];
    }
};

class Multiply : public Signal<double>
{

public:
    use_name( "Multiply" );

    SignalReaderWithName<"a", double> a{ this };
    SignalReaderWithName<"b", double> b{ this };


    void action() override
    {
        output = a[t] * b[t];
    }
};

class Divide : public Signal<double>
{

public:
    use_name( "Divide" );

    SignalReaderWithName<"numerator", double>   numerator{ this };
    SignalReaderWithName<"denominator", double> denominator{ this };


    void action() override
    {
        output = numerator[t] / denominator[t];
    }
};

class MonoToStereo : public StereoSignal
{

public:
    use_name( "MonoToStereo" );

    SignalReaderWithName<"input", double> input{ this };

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
    use_name( "Repeater" );

    SignalReaderWithName<"input", T> input{ this };

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
    use_name( "Clock" );

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
    use_name( "Accumulator" );

    SignalReaderWithName<"input", double> input{ this };

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
    use_name( "Modulo" );

    SignalReaderWithName<"input", double>   input{ this };
    SignalReaderWithName<"maximum", double> maximum{ this };

    void action() override
    {
        output = fmod( input[t], maximum[t] );
    }
};

class Noise : public Signal<double>
{
private:
    Random random;

public:
    use_name( "Noise" );

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

    use_name( "VectorSignal" );
};

class Sampler : public Signal<double>, WithName<"Sampler">
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

    use_name( "Sampler" );
};

class Wavetable : public Signal<double>
{
public:
    // TODO: make it multi channel
    MonoBuffer* buffer;

    SignalReaderWithName<"phase", double> phase{ this };

    Wavetable( MonoBuffer* buffer )
    : buffer( buffer )

    {
    }

    void action() override
    {

        output = buffer->interpolate( phase[t] * double( buffer->numberOfSamples ) );
    }

    use_name( "Wavetable" );
};

template <typename T>
class Wait : public Signal<T>
{
public:
    int                              waitTime;
    SignalReaderWithName<"input", T> input{ this };

    Wait( int countdown )
    : waitTime( countdown )
    {
    }

    void action() override
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

    use_name( "Wait" );
};

template <typename T>
class Skip : public Signal<T>
{
public:
    int                              skipTime;
    SignalReaderWithName<"input", T> input{ this };

    Skip( int skipTime )
    : skipTime( skipTime )
    {
    }

    void action() override
    {
        this->output = input[this->t + skipTime];
    }

    use_name( "Skip" );
};

template <typename T>
class Elapse : public Signal<T>
{
public:
    use_name( "Elapse" );

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
    SignalReaderWithName<"interval", double> interval{ this };


    void action() override
    {
        output = pow( 2.0, interval[t] / 12.0 );
    }

    use_name( "IntervalToRatio" );
};


class BufferLooper : public Signal<double>
{
public:
    std::vector<double> buffer;

    SignalReaderWithName<"input", double> input{ this };

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

    use_name( "BufferLooper" );
};

template <typename T>
class HardClip : public Signal<T>
{
public:
    SignalReaderWithName<"input", T> input{ this };

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

    use_name( "HardClip" );
};

class LinearRamp : public Signal<double>
{
public:
    SignalReaderWithName<"before", double>   before{ this };
    SignalReaderWithName<"duration", double> duration{ this };
    SignalReaderWithName<"after", double>    after{ this };

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

    use_name( "LinearRamp" );
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
