#include "record.h"

void record( const std::string& outputFile, FrameStream<double>& signal, float duration )
{

    std::ofstream outputStream( outputFile, std::ios::binary );

    record( outputStream, signal, duration );
}

void record( std::ostream& outputFile, FrameStream<double>& signal, float duration )
{

    double attenuation = .5;

    int numberOfFrames = duration * sampleRate;
    std::cerr << "Number of frames: " << numberOfFrames << "\n";
    WavWriter recorder( outputFile, numberOfFrames );
    for ( int i = 0; i < numberOfFrames; ++i )
    {
        recorder << signal[i] * attenuation;
    }
}
