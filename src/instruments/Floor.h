#pragma once

#include "../core.h"
#include <cmath>

class Floor : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> input{ this, "input" };

    void action()
    {
        output[0] = floor( input.readFrame() );
    }
};
