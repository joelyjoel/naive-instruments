#pragma once

#include "./Waveforms.h"
#include "./signal-processes.h"
#include <ctime>
#include <memory>

namespace NaiveInstruments
{
namespace SignalShorthands
{

typedef std::shared_ptr<Signal<double>>      mono;
typedef std::shared_ptr<Signal<StereoFrame>> stereo;

inline mono constant( double value )
{
    auto signal    = std::make_shared<Signal<double>>();
    signal->output = value;
    return signal;
}

inline mono t()
{
    return std::make_shared<Clock<double>>();
}

inline mono usaw( mono frequency )
{
    auto saw       = std::make_shared<USaw>();
    saw->frequency = frequency;
    return saw;
}

inline mono add( mono a, mono b )
{
    auto adder    = std::make_shared<Sum<double>>();
    adder->input1 = a;
    adder->input2 = b;
    return adder;
}

inline mono operator+( mono a, mono b )
{
    return add( a, b );
}

inline mono operator+( mono a, double b )
{
    return add( a, constant( b ) );
}
inline mono operator+( double a, mono b )
{
    return add( constant( a ), b );
}

inline mono subtract( mono a, mono b )
{
    auto subtracter = std::make_shared<NaiveInstruments::Subtract<double>>();
    subtracter->a   = a;
    subtracter->b   = b;
    return subtracter;
}

inline mono operator-( mono a, mono b )
{
    return subtract( a, b );
}

inline mono operator-( mono a, double b )
{
    return subtract( a, constant( b ) );
}

inline mono operator-( double a, mono b )
{
    return subtract( constant( a ), b );
}

inline mono operator-( mono a )
{
    auto flip   = std::make_shared<SignFlip>();
    flip->input = a;
    return flip;
}

inline mono multiply( mono a, mono b )
{
    auto multiplied = std::make_shared<NaiveInstruments::Multiply>();
    multiplied->a   = a;
    multiplied->b   = b;
    return multiplied;
}

inline mono operator*( mono a, mono b )
{
    return multiply( a, b );
}

inline mono operator*( mono a, double b )
{
    return a * constant( b );
}

inline mono operator*( double a, mono b )
{
    return constant( a ) * b;
}

inline mono divide( mono a, mono b )
{
    auto divided         = std::make_shared<NaiveInstruments::Divide>();
    divided->numerator   = a;
    divided->denominator = b;
    return divided;
}

inline mono operator/( mono a, mono b )
{
    return divide( a, b );
}

inline mono operator/( mono a, double b )
{
    return a / constant( b );
}

inline mono operator/( double a, mono b )
{
    return constant( a ) / b;
}

inline mono noise( uint64_t seed = 1 )
{
    return std::make_shared<Noise>( seed );
}


inline mono sampler( MonoBuffer* buffer )
{
    return std::make_shared<NaiveInstruments::Sampler>( buffer );
}

inline mono wavetable( MonoBuffer* buffer, mono phase )
{
    auto signal   = std::make_shared<Wavetable>( buffer );
    signal->phase = phase;
    return signal;
}

inline mono wavetableFromFile( const std::string& filePath, mono phase )
{
    return wavetable( &Waveforms::fromFile( filePath ), phase );
}

inline mono squareWavetable( mono phase )
{
    return wavetable( &Waveforms::square(), phase );
}

inline mono sineWavetable( mono phase )
{
    return wavetable( &Waveforms::sine(), phase );
}

inline mono square( mono frequency )
{
    return wavetable( &Waveforms::square(), usaw( frequency ) );
}

inline mono sine( mono frequency )
{
    return wavetable( &Waveforms::sine(), usaw( frequency ) );
}

inline mono saw( mono frequency )
{
    return wavetable( &Waveforms::saw(), usaw( frequency ) );
}

inline mono triangle( mono frequency )
{
    return wavetable( &Waveforms::triangle(), usaw( frequency ) );
}


inline mono oscWithWavetableFromFile( const std::string& filePath, mono frequency )
{
    return wavetableFromFile( filePath, usaw( frequency ) );
}


}; // namespace SignalShorthands
} // namespace NaiveInstruments
