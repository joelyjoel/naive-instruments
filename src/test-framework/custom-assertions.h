#include "../../dependencies/catch.hpp"
#include "../Signal.h"
#include "../file-io/WavWriter.h"
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

inline void AUDIO_TEST( const std::string&                                name,
                        std::shared_ptr<NaiveInstruments::Signal<double>> signal,
                        double                                            duration = .1 )
{
    std::filesystem::create_directory( "./expected-samples" );
    std::string expectedChecksumPath = "./expected-samples/" + name + ".checksum.txt";
    std::string expectedChecksum     = "?";
    if ( std::filesystem::exists( expectedChecksumPath ) )
    {
        std::ifstream expectedChecksumFile( expectedChecksumPath );
        getline( expectedChecksumFile, expectedChecksum );
    }

    std::string auditionSamplePath = "./audition/" + name + ".wav";

    WavWriter                              writer( auditionSamplePath, duration * 44100 );
    double                                 sum = 0;
    NaiveInstruments::SignalReader<double> reader;
    reader = signal;
    for ( int t = 0; t < 44100 * duration; ++t )
    {
        // TODO: This part needs re rewriting
        writer << reader[t];
        sum += reader[t];
    }
    sum                        = fmod( sum, 1.0 );
    std::string actualChecksum = std::to_string( sum );

    if ( expectedChecksum == "?" )
    {
        std::filesystem::create_directory( "./audition" );
        std::string   auditionChecksumPath = "./audition/" + name + ".checksum.txt";
        std::ofstream auditionChecksumFile( auditionChecksumPath );
        auditionChecksumFile << actualChecksum;
        FAIL( "No expected checksum for " + name + ". Please review `" + auditionChecksumPath
              + "` and move to `./expected-samples` if satisfied." );
    }
    else
    {
        REQUIRE( actualChecksum == expectedChecksum );
        if ( actualChecksum == expectedChecksum )
            std::filesystem::remove( auditionSamplePath );
    }
}
