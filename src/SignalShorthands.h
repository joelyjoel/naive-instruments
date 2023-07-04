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

inline mono noise( uint64_t seed = 1 )
{
    return std::make_shared<Noise>( seed );
}


inline mono constant( double value )
{
    auto signal    = std::make_shared<Signal<double>>();
    signal->output = value;
    return signal;
}


inline mono sampler( MonoBuffer* buffer )
{
    return std::make_shared<NaiveInstruments::Sampler>( buffer );
}

inline mono sineWavetable( mono phase )
{
    auto signal   = std::make_shared<NaiveInstruments::Wavetable>( &Waveforms::sine() );
    signal->phase = phase;
    return signal;
}

inline mono sine( mono frequency )
{
    return sineWavetable( usaw( frequency ) );
}

}; // namespace SignalShorthands
} // namespace NaiveInstruments
