#pragma once

#include "../core.h"
#include <iostream>

template <typename Frame>
class Constant : public FrameStream<Frame>
{
private:
    Frame value = 0;

public:
    Constant( Frame k )
    : value( k )
    {
    }
    void action()
    {
        FrameStream<Frame>::output[0] = value;
    }
};
