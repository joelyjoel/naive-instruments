#include "../../dependencies/catch.hpp"
#include "../file-io/WavWriter.h"
#include "../signal/Signal.h"
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
    WavWriter                              writer( outputPath, durationInSamples );
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


inline void AUDIO_TEST( const std::string&                                name,
                        std::shared_ptr<NaiveInstruments::Signal<double>> signal,
                        double                                            duration = .5 )
{
    std::filesystem::create_directory( "./expected-samples" );
    std::string expectedChecksumPath = "./expected-samples/" + name + ".checksum.txt";
    std::string expectedChecksum     = "?";
    INFO( "expectedChecksumPath: " + expectedChecksumPath );
    if ( std::filesystem::exists( expectedChecksumPath ) )
    {
        std::ifstream expectedChecksumFile( expectedChecksumPath );
        getline( expectedChecksumFile, expectedChecksum );
    }
    INFO( "expectedChecksum: " + expectedChecksum );

    std::string auditionSamplePath = "./audition/" + name + ".wav";
    INFO( "auditionSamplePath: " + auditionSamplePath );
    std::string expectedSamplePath = "./expected-samples/" + name + ".wav";
    INFO( "expectedSamplePath: " + expectedSamplePath );
    std::string actualChecksum = record_and_checksum( auditionSamplePath, signal, duration * 44100 );
    INFO( "actualChecksum: " + actualChecksum );

    if ( expectedChecksum == "?" )
    {
        std::filesystem::create_directory( "./audition" );
        std::string auditionChecksumPath = "./audition/" + name + ".checksum.txt";
        INFO( "auditionChecksumPath = " + auditionChecksumPath );
        std::ofstream auditionChecksumFile( auditionChecksumPath );
        auditionChecksumFile << actualChecksum;
        FAIL( "No expected checksum for " + name + ". Please review `" + auditionChecksumPath
              + "` and move to `./expected-samples` if satisfied." );
    }
    else
    {
        CHECK( actualChecksum == expectedChecksum );
        if ( actualChecksum == expectedChecksum )

        {
            if ( !std::filesystem::exists( expectedSamplePath ) )
                std::filesystem::rename( auditionSamplePath, expectedSamplePath );
            std::filesystem::remove( auditionSamplePath );
        }
    }
}
