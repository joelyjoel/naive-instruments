#include "../core/MonoBuffer.h"
#include "./Signal.h"

namespace NaiveInstruments
{

/**
 * Record a signal into a MonoBuffer.
 */
std::shared_ptr<MonoBuffer> recordMonoBuffer( std::shared_ptr<Signal<double>> signal, float duration );

}; // namespace NaiveInstruments
