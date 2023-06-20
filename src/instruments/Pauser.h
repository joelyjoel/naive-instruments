#pragma once

#include "../lib.h"

class Pauser : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> input{ this, "input", false };

private:
    bool paused = false;
    int  t      = 0;

public:
    void pause()
    {
        paused = true;
    }
    void resume()
    {
        paused = false;
    }
    void toggle()
    {
        paused = !paused;
    }

    bool is_paused()
    {
        return paused == true;
    }

    void action() override
    {
        if ( paused )
            output[0] = 0;
        else
        {
            input.sync( t++ );
            output[0] = input.readFrame();
        }
    }
};
