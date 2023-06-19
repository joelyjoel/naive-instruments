#pragma once

#include "../core.h"

const int LIMIT_EXCEEDED = 99;

/**
 * Use this to wait for bangs (true values in a boolean signal);
 */
class BangAwaiter
{
private:
    shared_ptr<FrameStream<bool>> signal;

public:
    void next( int limit = 44100 )
    {
        while ( signal->advanceToNextFrameAndRead() == false )
            if ( --limit > 0 )
                continue;
            else
                throw LIMIT_EXCEEDED;
    }

    void operator<<( shared_ptr<FrameStream<bool>> input )
    {
        signal = input;
    }
};
