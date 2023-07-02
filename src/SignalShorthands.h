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

}; // namespace SignalShorthands
} // namespace NaiveInstruments
