#pragma once

#include "../lib.h"
#include <memory>

class WaveformBufferer
{
private:
    std::shared_ptr<BufferWriter>         bufferer;
    std::shared_ptr<ZeroCrossingDetector> detector = std::make_shared<ZeroCrossingDetector>();
    BangAwaiter                           waiter;

    std::shared_ptr<FrameStream<double>> input;

    void assemble()
    {
        waiter << detector;
        detector->input << bufferer;
    }

public:
    WaveformBufferer()
    {
        bufferer = std::make_shared<BufferWriter>( 4096 );
        assemble();
    }

public:
    int minNumberOfFrames = 0;

private:
    int index = -1;

    std::shared_ptr<MonoBuffer> copyNextWaveform()
    {
        do
        {
            bufferer.reset();
            waiter.next();
        } while ( bufferer->currentSize() < minNumberOfFrames );
        ++index;
        return bufferer->copyBuffer();
    }

    void skipNextWaveform()
    {
        do
        {
            bufferer.reset();
            waiter.next();
        } while ( bufferer->currentSize() < minNumberOfFrames );
        ++index;
    }

    void reset()
    {
        bufferer.reset();
        detector.reset();
        input->reset();
    }

    void skipTo( int destinationIndex )
    {
        if ( destinationIndex < index )
            reset();
        while ( index < destinationIndex )
            skipNextWaveform();
    }

public:
    std::shared_ptr<MonoBuffer> select( int waveformIndex )
    {
        skipTo( waveformIndex );
        return copyNextWaveform();
    }

    std::shared_ptr<MonoBuffer> operator[]( int waveformIndex )
    {
        return select( waveformIndex );
    }

    void operator<<( std::shared_ptr<FrameStream<double>> inputSignal )
    {
        bufferer->input << inputSignal;
    }
};
