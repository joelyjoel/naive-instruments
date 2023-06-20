#include "AbstractFrameStream.h"

template <typename frame>
class FrameStream : public AbstractFrameStream
{
protected:
    frame* output                 = nullptr;
    short  numberOfOutputChannels = 0;


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

private:
    void setNumberOfOutputChannels( int numberOfChannels )
    {
        // Deallocate if it its already been set
        if ( output != nullptr )
            delete output;
        numberOfOutputChannels = numberOfChannels;
        output                 = new frame[numberOfOutputChannels];
    }

    short getNumberOfOuptutChannels()
    {
        return numberOfOutputChannels;
    }


protected:
    /**
     * Update the latest frame.
     */
    void writeFrame( const frame& y )
    {
        *output = y;
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
