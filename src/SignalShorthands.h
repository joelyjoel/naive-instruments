#pragma once

#include "./signal-processes.h"
#include <ctime>
#include <memory>

namespace NaiveInstruments
{
namespace SignalShorthands
{

typedef std::shared_ptr<Signal<double>>      mono;
typedef std::shared_ptr<Signal<StereoFrame>> stereo;

mono t();

mono usaw( mono frequency );

mono add( mono a, mono b );

mono operator+( mono a, mono b );

mono noise( uint64_t seed = 1 );

mono constant( double value );

mono sampler( MonoBuffer* buffer );

mono sineWavetable( mono phase );

mono sine( mono frequency );

}; // namespace SignalShorthands
} // namespace NaiveInstruments
