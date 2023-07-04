#include "./SignalShorthands.h"
#include "./Waveforms.h"
#include "core/MonoBuffer.h"
#include <memory>

using namespace NaiveInstruments;
using SignalShorthands::mono;

mono SignalShorthands::t()
{
    return std::make_shared<Clock<double>>();
}

mono SignalShorthands::usaw( mono frequency )
{
    auto saw       = std::make_shared<USaw>();
    saw->frequency = frequency;
    return saw;
}

mono SignalShorthands::add( mono a, mono b )
{
    auto adder    = std::make_shared<Sum<double>>();
    adder->input1 = a;
    adder->input2 = b;
    return adder;
}

mono SignalShorthands::operator+( mono a, mono b )
{
    return add( a, b );
}


mono SignalShorthands::noise( uint64_t seed )
{
    return std::make_shared<Noise>( seed );
}

mono SignalShorthands::constant( double value )
{
    auto signal    = std::make_shared<Signal<double>>();
    signal->output = value;
    return signal;
}

mono SignalShorthands::sampler( MonoBuffer* buffer )
{
    return std::make_shared<NaiveInstruments::Sampler>( buffer );
}

mono SignalShorthands::sineWavetable( mono phase )
{
    auto signal   = std::make_shared<NaiveInstruments::Wavetable>( &Waveforms::sine() );
    signal->phase = phase;
    return signal;
}
