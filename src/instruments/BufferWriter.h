#pragma once

#include "../core.h"

class BufferWriter : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> input = { this, "input" };

private:
    MonoBuffer* buffer;

public:
    BufferWriter( int bufferSize )
    {
        buffer = new MonoBuffer( bufferSize );
    }
    ~BufferWriter()
    {
        if ( buffer != nullptr )
            delete buffer;
        buffer = nullptr;
    }

private:
    int writeHead = 0;

public:
    void action()
    {
        double signal = input.readFrame();
        if ( writeHead < buffer->numberOfFrames() )
            ( *buffer )[writeHead] = signal;
        ++writeHead;
        output[0] = signal;
    }

    int currentSize()
    {
        return writeHead;
    }
    std::shared_ptr<MonoBuffer> copyBuffer()
    {
        return buffer->slice( 0, currentSize() );
    }

    void reset()
    {
        writeHead = 0;
    }

    std::shared_ptr<MonoBuffer> copyAndReset()
    {
        auto ptr = copyBuffer();
        reset();
        return ptr;
    }
};
