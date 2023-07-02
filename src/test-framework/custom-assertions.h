#include "../../dependencies/catch.hpp"
#include "../Signal.h"

template <typename T>
void CHECK_SIGNAL( std::shared_ptr<NaiveInstruments::Signal<T>> signal, std::vector<T> expectedSequence )
{
    NaiveInstruments::SignalReader<T> reader;
    reader = signal;
    for ( int i = 0; i < expectedSequence.size(); ++i )
        SECTION( "Comparing frame " + std::to_string( i ) )
        {
            CHECK( reader[i] == expectedSequence[i] );
        }
}
