#pragma once

#include "AbstractFrameStream.h"
#include "constants.h"

template <typename frame>
class FrameStream : public AbstractFrameStream
{
protected:
    frame* output = nullptr;


public:
    FrameStream()
    {
        setNumberOfOutputChannels( 1 );
    }
    ~FrameStream()
    {
        delete output;
        output = nullptr;
    }

protected:
    void setNumberOfOutputChannels( int numberOfChannels )
    {
        // Deallocate if it its already been set
        if ( output != nullptr )
        {
            delete output;
            output = nullptr;
        }

        if ( numberOfChannels != numberOfOutputChannels )
        {
            numberOfOutputChannels = numberOfChannels;
            if ( numberOfOutputChannels == 0 )
            {
                output = nullptr;
            }
            else
            {
                output = new frame[numberOfOutputChannels];
            }
            for ( auto stream : readingStreams() )
            {
                stream->handleConnectionChange();
            }
        }
    }


public:
    frame operator[]( int clock )
    {
        sync( clock );
        return readFrame();
    }

    frame readFrame()
    {
        return *output;
    }

    frame advanceToNextFrameAndRead()
    {
        advanceToNextFrame();
        return readFrame();
    }

    AbstractFrameStreamConsumer& defaultInput()
    {
        if ( inputs.size() > 0 )
            return *inputs[0];
        else
        {
            std::cerr << "Trying to get default input but the Signal has no inputs";
            throw 1;
        }
    }

    void operator<<( double k )
    {
        defaultInput().setConstant( k );
    }

public:
    std::string summary() override
    {
        return label() + "[" + std::to_string( internalClock ) + "] = " + std::to_string( *output );
    }
};
