#include "record.h"

void record( const std::string& outputFile, std::shared_ptr<FrameStream<double>> signal, float duration )
{

    double attenuation    = .5;
    int    numberOfFrames = duration * sampleRate;
    std::cerr << "Number of frames: " << numberOfFrames << "\n";
    WavWriter recorder( outputFile.c_str(), numberOfFrames );
    for ( int i = 0; i < numberOfFrames; ++i )
        recorder << ( *signal )[i] * attenuation;
}

void record( const std::string& outputFile, NaiveInstruments::SignalShorthands::mono signal, float duration )
{

    double attenuation = .5;

    int numberOfFrames = duration * sampleRate;
    std::cerr << "Number of frames: " << numberOfFrames << "\n";
    WavWriter recorder( outputFile.c_str(), numberOfFrames );

    NaiveInstruments::SignalReader<double> reader;
    reader = signal;

    for ( int i = 0; i < numberOfFrames; ++i )
        recorder << reader[i] * attenuation;
}

[[deprecated( "Writing wav files to pipes is a bad idea because the duration must be specified in the header" )]] void
recordToStdout( std::shared_ptr<FrameStream<double>> signal, float duration )
{
    double attenuation    = .5;
    int    numberOfFrames = duration * sampleRate;
    std::cerr << "Number of frames: " << numberOfFrames << "\n";
    WavWriter recorder( stdout, numberOfFrames );
    for ( int i = 0; i < numberOfFrames; ++i )
    {
        recorder << ( *signal )[i] * attenuation;
    }
}

void recordToStdout( NaiveInstruments::SignalShorthands::mono signal, float duration )
{
    double attenuation = .5;


    int numberOfFrames = duration * sampleRate;
    std::cerr << "Number of frames: " << numberOfFrames << "\n";
    WavWriter recorder( stdout, numberOfFrames );

    NaiveInstruments::SignalReader<double> reader;
    reader = signal;

    for ( int i = 0; i < numberOfFrames; ++i )
    {
        recorder << reader[i] * attenuation;
    }
};
