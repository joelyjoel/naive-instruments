#include "../../dependencies/catch.hpp"
#include "../Signal.h"

inline void CHECK_SIGNAL( std::shared_ptr<NaiveInstruments::Signal<double>> signal,
                          std::vector<double>                               expectedSequence )
{
    NaiveInstruments::SignalReader<double> reader;
    reader = signal;
    for ( int i = 0; i < expectedSequence.size(); ++i )
        SECTION( "Comparing frame " + std::to_string( i ) )
        {
            CHECK( reader[i] == Approx( expectedSequence[i] ) );
        }
}

inline void CHECK_SIGNAL( std::shared_ptr<NaiveInstruments::Signal<NaiveInstruments::StereoFrame>> signal,
                          std::vector<NaiveInstruments::StereoFrame>                               expectedSequence )
{
    NaiveInstruments::SignalReader<NaiveInstruments::StereoFrame> reader;
    reader = signal;
    for ( int i = 0; i < expectedSequence.size(); ++i )
        SECTION( "Comparing frame " + std::to_string( i ) )
        {
            CHECK( reader[i].left == Approx( expectedSequence[i].left ) );
            CHECK( reader[i].right == Approx( expectedSequence[i].right ) );
        }
}

inline void CHECK_FRAME( std::shared_ptr<NaiveInstruments::Signal<double>> signal, int frame, double expectedValue )
{
    SECTION( "Checking frame " + std::to_string( frame ) )
    {
        signal->sync( frame );
        CHECK( signal->output == Approx( expectedValue ) );
    }
}
