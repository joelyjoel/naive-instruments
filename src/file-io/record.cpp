#include "record.h"

void record( const std::string& outputFile, std::shared_ptr<FrameStream<double>> signal, float duration )
{

    std::ofstream outputStream( outputFile, std::ios::binary );

    record( outputStream, signal, duration );
}

void record( const std::string& outputFile, NaiveInstruments::SignalShorthands::mono signal, float duration )
{

    std::ofstream outputStream( outputFile, std::ios::binary );
    record( outputStream, signal, duration );
}

void record( std::ostream& outputFile, std::shared_ptr<FrameStream<double>> signal, float duration )
{

    double attenuation = .5;

    int numberOfFrames = duration * sampleRate;
    std::cerr << "Number of frames: " << numberOfFrames << "\n";
    WavWriter recorder( outputFile, numberOfFrames );
    for ( int i = 0; i < numberOfFrames; ++i )
    {
        recorder << ( *signal )[i] * attenuation;
    }
}

void record( std::ostream& outputStream, NaiveInstruments::SignalShorthands::mono signal, float duration )
{

    double attenuation = .5;

    int numberOfFrames = duration * sampleRate;
    std::cerr << "Number of frames: " << numberOfFrames << "\n";
    WavWriter recorder( outputStream, numberOfFrames );

    NaiveInstruments::SignalReader<double> reader;
    reader = signal;

    for ( int i = 0; i < numberOfFrames; ++i )
    {
        recorder << reader[i] * attenuation;
    }
};
