#include "./recordMonoBuffer.h"
#include <memory>


namespace NaiveInstruments
{
std::shared_ptr<MonoBuffer> recordMonoBuffer( std::shared_ptr<Signal<double>> signal, float duration )
{
    int  numberOfFrames = duration * 44100;
    auto buffer         = std::make_shared<MonoBuffer>( numberOfFrames );

    SignalReader<double> reader;
    reader = signal;

    for ( int t = 0; t < numberOfFrames; ++t )
    {
        ( *buffer )[t] = reader[t];
    }
    return buffer;
}
}; // namespace NaiveInstruments
