#pragma once

#include <exception>
#include <iostream>
#include <portaudio.h>
#include <thread>

#include "../core.h"

#include "../SignalShorthands.h"
#include "../instruments/Constant.h"
#include "../instruments/Sampler.h"
#include "./CircularBuffer.h"

using NaiveInstruments::SignalShorthands::mono;

static int audioCallback( const void*                     inputBuffer,
                          void*                           outputBuffer,
                          unsigned long                   framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags           statusFlags,
                          void*                           userData );


static int audioSignalCallback( const void*                     inputBuffer,
                                void*                           outputBuffer,
                                unsigned long                   framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeInfo,
                                PaStreamCallbackFlags           statusFlags,
                                void*                           userData );

class BufferedPlayback
{
private:
    PaStream* stream;
    PaError   err;

public:
    BufferedPlayback( FrameStream<double>& input )
    : buffer( 1024 )
    {
        signal = &input;
    }
    BufferedPlayback()
    : BufferedPlayback( *new Constant<double>( 0 ) )
    {
    }
    FrameStream<double>*   signal;
    CircularBuffer<double> buffer;
    double                 shift()
    {
        return buffer.shift();
    }
    void push( double y )
    {
        buffer.push( y );
    }

    void assertNotError()
    {
        if ( err != paNoError )
        {
            std::cerr << "Port audio error:" << Pa_GetErrorText( err ) << "\n";
            throw 1;
        }
    }

    void startAudioThread();

    std::thread* topUpThread;
    void         startTopUpThread()
    {
        topUpThread = new std::thread( [this]() {
            while ( true )
                this->topUpBufferAndSleep();
        } );
    }

    void start( bool async = false )
    {
        topUpBuffer();
        startAudioThread();
        startTopUpThread();
        if ( async )
            topUpThread->detach();
        else
            topUpThread->join();
    }

    void stop()
    {
        std::cout << "Stopping stream\n";
        err = Pa_StopStream( stream );
        assertNotError();

        std::cout << "Terminating port audio\n";
        err = Pa_Terminate();
        assertNotError();
    }

    void topUpBuffer()
    {
        while ( buffer.hasFreeSpace() )
            buffer.push( signal->advanceToNextFrameAndRead() );
    }

    void topUpBufferAndSleep()
    {
        topUpBuffer();
        Pa_Sleep( idealTopUpInterval() * 1000 * .25 );
    }

    double idealTopUpInterval()
    {
        return float( buffer.size() ) / float( sampleRate );
    }

    static void play( FrameStream<double>& signal )
    {
        BufferedPlayback playback( signal );
        playback.start( false );
    }

    static void play( MonoBuffer& audio )
    {
        Sampler sampler( audio );
        play( sampler );
    }

    void setSignal( FrameStream<double>& sound )
    {
        signal = &sound;
    }
    void setSignal( MonoBuffer& sample )
    {
        // FIXME: Memory leak!
        Sampler* sampler = new Sampler( sample );
        setSignal( *sampler );
    }

    void resetSignal()
    {
        signal->reset();
    }
};

class BufferedSignalPlayback
{
private:
    PaStream* stream;
    PaError   err;

public:
    BufferedSignalPlayback( mono input )
    : buffer( 1024 )
    {
        signal = input;
    }
    BufferedSignalPlayback()
    : BufferedSignalPlayback( NaiveInstruments::SignalShorthands::constant( 0 ) )
    {
    }
    NaiveInstruments::SignalReader<double> signal;
    CircularBuffer<double>                 buffer;
    double                                 shift()
    {
        return buffer.shift();
    }
    void push( double y )
    {
        buffer.push( y );
    }

    void assertNotError()
    {
        if ( err != paNoError )
        {
            std::cerr << "Port audio error:" << Pa_GetErrorText( err ) << "\n";
            throw 1;
        }
    }

    void startAudioThread();

    std::thread* topUpThread;
    void         startTopUpThread()
    {
        topUpThread = new std::thread( [this]() {
            while ( true )
                this->topUpBufferAndSleep();
        } );
    }

    void start( bool async = false )
    {
        topUpBuffer();
        startAudioThread();
        startTopUpThread();
        if ( async )
            topUpThread->detach();
        else
            topUpThread->join();
    }

    void stop()
    {
        std::cout << "Stopping stream\n";
        err = Pa_StopStream( stream );
        assertNotError();

        std::cout << "Terminating port audio\n";
        err = Pa_Terminate();
        assertNotError();
    }

    int  t = 0;
    void topUpBuffer()
    {
        while ( buffer.hasFreeSpace() )
            buffer.push( signal[++t] );
    }

    void topUpBufferAndSleep()
    {
        topUpBuffer();
        Pa_Sleep( idealTopUpInterval() * 1000 * .25 );
    }

    double idealTopUpInterval()
    {
        return float( buffer.size() ) / float( sampleRate );
    }

    static void play( mono signal )
    {
        BufferedSignalPlayback playback( signal );
        playback.start( false );
    }

    static void play( MonoBuffer& audio )
    {
        play( NaiveInstruments::SignalShorthands::sampler( &audio ) );
    }

    void setSignal( mono sound )
    {
        signal = sound;
    }
    void setSignal( MonoBuffer& sample )
    {
        setSignal( NaiveInstruments::SignalShorthands::sampler( &sample ) );
    }
};
