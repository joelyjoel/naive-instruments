#pragma once
#include "../core.h"
class AHD : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> attack{ this, "attack/s" };
    FrameStreamConsumer<double> hold{ this, "hold/s" };
    FrameStreamConsumer<double> decay{ this, "decay/s" };

private:
    enum AHDStage
    {
        A,
        H,
        D,
        finished
    };
    double   phase = 0;
    AHDStage stage = A;

    void action()
    {

        switch ( stage )
        {

            case A:
                phase += 1 / sampleRate / attack.readFrame();
                if ( phase >= 1 )
                {
                    phase = 0;
                    stage = H;
                }
                output[0] = phase;
                break;

            case H:
                phase += 1 / sampleRate / hold.readFrame();
                if ( phase >= 1 )
                {
                    phase = 0;
                    stage = D;
                }
                output[0] = 1;
                break;

            case D:
                phase += 1 / sampleRate / decay.readFrame();
                if ( phase >= 1 )
                {
                    phase = 0;
                    stage = finished;
                }
                output[0] = 1 - phase;
                break;

            case finished:
                output[0] = 0;
                break;
        }
    }
};
