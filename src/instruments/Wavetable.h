#pragma once

#include "../Waveforms.h"
#include "../core.h"
#include <string>

class Wavetable : public FrameStream<double>
{
    int bufferLength;

    MonoBuffer* waveform;

public:
    std::string label()
    {
        return "Wavetable";
    }

    FrameStreamConsumer<double> phase{ this, "phase/0-1" };

    Wavetable( MonoBuffer& waveform = Waveforms::sine() )
    : waveform( &waveform )
    {
    }

    void action()
    {
        output[0] = waveform->interpolate( phase.readFrame() * double( waveform->numberOfSamples ) );
    }

    void setWaveform( MonoBuffer* buffer )
    {
        waveform = buffer;
    }
    void setWaveform( MonoBuffer& buffer )
    {
        waveform = &buffer;
    }
};
