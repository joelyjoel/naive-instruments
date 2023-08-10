#pragma once

#include "../Waveforms.h"
#include "../core.h"
#include "UnsignedSaw.h"
#include "Wavetable.h"
#include <iostream>
#include <string>

// TODO: Probably could be converted into a function or something once shared
// pointers are fully adopted
class Osc : public Patch<double>
{
    std::shared_ptr<UnsignedSaw> phase{ std::make_shared<UnsignedSaw>() };
    std::shared_ptr<Wavetable>   wavetable{ std::make_shared<Wavetable>() };

public:
    FrameStreamConsumer<double>& frequency = exposeInput( phase->frequency );

public:
    // TODO: Make it a private constructor
    Osc( MonoBuffer& waveform )
    {
        wavetable->phase << phase;
        wavetable->setWaveform( waveform );
        exposeOutput( wavetable );
    }

    std::string label() override
    {
        return "Osc";
    }

    static std::shared_ptr<Osc> create( MonoBuffer& waveform )
    {
        return std::make_shared<Osc>( waveform );
    }
    static std::shared_ptr<Osc> create_sine()
    {
        return create( Waveforms::sine() );
    }
    static std::shared_ptr<Osc> create_square()
    {
        return create( Waveforms::square() );
    }
    static std::shared_ptr<Osc> create_saw()
    {
        return create( Waveforms::saw() );
    }
    static std::shared_ptr<Osc> create_triangle()
    {
        return create( Waveforms::triangle() );
    }
};

std::shared_ptr<FrameStream<double>> sine( std::shared_ptr<FrameStream<double>> frequency );
std::shared_ptr<FrameStream<double>> sine( double frequency );
std::shared_ptr<FrameStream<double>> saw( std::shared_ptr<FrameStream<double>> frequency );
std::shared_ptr<FrameStream<double>> square( std::shared_ptr<FrameStream<double>> frequency );
std::shared_ptr<FrameStream<double>> triangle( std::shared_ptr<FrameStream<double>> frequency );
