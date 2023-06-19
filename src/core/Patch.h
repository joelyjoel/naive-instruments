#pragma once

#include "Signal.h"
#include <string>

template <typename SignalFrame>
class Patch : public FrameStream<SignalFrame>
{
private:
    /**
     * Pointer to the signal nominated as this patch's output signal.
     */
    shared_ptr<FrameStream<SignalFrame>> outputFrameStream;

public:
public:
    void action()
    {
        outputFrameStream->sync( this->internalClock );
        this->writeFrame( outputFrameStream->readFrame() );
    }

protected:
    template <typename T>
    FrameStreamConsumer<T>& exposeInput( FrameStreamConsumer<T>& input )
    {
        FrameStream<SignalFrame>::inputs.push_back( &input );
        return input;
    }

protected:
    void exposeOutput( shared_ptr<FrameStream<SignalFrame>> outputSignal )
    {
        if ( !outputSignal )
        {
            std::cerr << "output pointer is null in " << label() << "\n";
            throw 1;
        }
        outputFrameStream = outputSignal;
    }

    std::string label()
    {
        return "Patch";
    }
};
