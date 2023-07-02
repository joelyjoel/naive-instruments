#pragma once

#include "./Signal.h"
#include <ctime>
#include <memory>

namespace NaiveInstruments
{
namespace SignalShorthands
{

typedef std::shared_ptr<Signal<double>>      mono;
typedef std::shared_ptr<Signal<StereoFrame>> stereo;

mono t();

mono add( mono a, mono b );

mono operator+( mono a, mono b );

mono noise( uint64_t seed = 1 );

mono constant( double value );

}; // namespace SignalShorthands
} // namespace NaiveInstruments
