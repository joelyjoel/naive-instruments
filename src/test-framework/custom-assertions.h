#include "../../dependencies/catch.hpp"
#include "../file-io/WavWriter.h"
#include "../signal/SignalShorthands.h"
#include <filesystem>
#include <fstream>
#include <math.h>
#include <string>

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

class Hasher
{
public:
    unsigned long checksum = 0;


    void operator()( double value )
    {
        char* recast = (char*) &value;
        for ( int i = 0; i < sizeof( double ); ++i )
        {
            checksum = checksum << 1;
            checksum += recast[i];
        }
    }
};


inline std::string record_and_checksum( const std::string                                 outputPath,
                                        std::shared_ptr<NaiveInstruments::Signal<double>> signal,
                                        int                                               durationInSamples )
{
    WavWriter                              writer( outputPath.c_str(), durationInSamples );
    NaiveInstruments::SignalReader<double> reader;
    reader = signal;

    Hasher hasher;

    for ( int t = 0; t < durationInSamples; ++t )
    {
        writer << reader[t];
        hasher( reader[t] );
    }

    return std::to_string( hasher.checksum );
}


inline const std::string referenceToneLocation = "./tests/results/";

inline void referenceToneTest( const std::string&                                                       name,
                               std::shared_ptr<NaiveInstruments::Signal<NaiveInstruments::StereoFrame>> signal,
                               double                                                                   duration = .1 )
{
    std::filesystem::create_directory( referenceToneLocation );
    std::string filepath = referenceToneLocation + name + ".wav";
    WavWriter   writer( filepath.c_str(), duration * 44100 );
    writer.write( signal, duration );
}

inline void referenceToneTest( const std::string&                                name,
                               std::shared_ptr<NaiveInstruments::Signal<double>> signal,
                               double                                            duration = .1 )
{
    return referenceToneTest( name, NaiveInstruments::SignalShorthands::monoToStereo( signal ), duration );
}
