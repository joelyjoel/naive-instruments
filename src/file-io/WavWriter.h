#pragma once

#include "../core.h"
#include "WAV_HEADER.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sndfile.h>
#include <stdio.h>

class WavWriter
{
    const char* filepath;
    SNDFILE*    file;
    SF_INFO     info;

    int numberOfSamplesWritten = 0;

public:
    WavWriter( const char* filepath, int numberOfFrames )
    : filepath( filepath )
    {
        initialise_info( numberOfFrames );
        file = sf_open( filepath, SFM_WRITE, &info );
        check_file();
    }

    WavWriter( FILE* fileStream, int numberOfFrames )
    : filepath( "?" )
    {
        initialise_info( numberOfFrames );
        int fileDescriptor = fileno( fileStream );
        file               = sf_open_fd( fileDescriptor,
                           SFM_WRITE,
                           &info,
                           // TODO: When should this be 1
                           0 );
        check_file();
    }

    ~WavWriter()
    {
        std::cerr << "WavWriter wrote " << numberOfSamplesWritten << " to " << filepath << std::endl;
        sf_close( file );
    }

private:
    void initialise_info( int numberOfFrames )
    {
        info.frames     = numberOfFrames;
        info.channels   = 2;
        info.samplerate = 44100;
        info.format     = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
        /* info.sections; ?  */
        info.seekable = false;
    }

    void check_file()
    {
        if ( !file )
        {
            std::cerr << "Unable to open wav file for writing: " << filepath << "\n";
            // TODO: Use proper exceptions
            throw 1;
        }
    }

public:
    void write( MonoBuffer& audioData )
    {
        int written = sf_write_double( file, audioData.data, audioData.numberOfSamples );
        numberOfSamplesWritten += written;
        if ( written != audioData.numberOfSamples )
        {
            std::cerr << "There was a problem recording a mono buffer to " << filepath << "\n";
            // TODO: Use proper exceptions
            throw 1;
        }
    }

    void write( int sample )
    {
        write( sample, sample );
    }

    void write( int left, int right )
    {
        int data[2] = { left, right };
        int written = sf_write_int( file, data, 2 );
        numberOfSamplesWritten += 2;
        if ( written != 2 )
        {
            std::cerr << "There was a problem writing a stereo frame (double[2]) sample to " << filepath << "\n";
            // TODO: Use proper exceptions
            throw 1;
        }
    }

    void write( double sample )
    {
        write( sample, sample );
    }

    double write( double left, double right )
    {
        double data[2] = { left, right };
        int    written = sf_write_double( file, data, 2 );
        numberOfSamplesWritten += 2;
        if ( written != 2 )
        {
            std::cerr << "There was a problem writing a stereo frame (double[2]) sample to " << filepath << "\n";
            // TODO: Use proper exceptions
            throw 1;
        }
    }

    template <typename T>
    void operator<<( T sample )
    {
        write( sample );
    }


    static int16_t doubleToInt16_t( double val )
    {
        // return 0;
        return INT16_MAX * val * .5;
    }


    static void write( const char* filepath, MonoBuffer& audioData )
    {
        const double attenuation = .9;
        WavWriter    recorder( filepath, audioData.numberOfFrames() );
        recorder.write( audioData );
    }

    [[deprecated(
        "Writing wav files to a pipe is a bad idea because the duration must be specified in the header" )]] static void
    writeToStdout( MonoBuffer& audioData )
    {
        const double attenuation = .9;
        WavWriter    recorder( stdout, audioData.numberOfFrames() );
        recorder.write( audioData );
    }
};
