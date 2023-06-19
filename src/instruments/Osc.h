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
    shared_ptr<UnsignedSaw> phase{ make_shared<UnsignedSaw>() };
    shared_ptr<Wavetable>   wavetable{ make_shared<Wavetable>() };

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

    static shared_ptr<Osc> create( MonoBuffer& waveform )
    {
        return make_shared<Osc>( waveform );
    }
    static shared_ptr<Osc> create_sine()
    {
        return create( Waveforms::sine() );
    }
    static shared_ptr<Osc> create_square()
    {
        return create( Waveforms::square() );
    }
    static shared_ptr<Osc> create_saw()
    {
        return create( Waveforms::saw() );
    }
    static shared_ptr<Osc> create_triangle()
    {
        return create( Waveforms::triangle() );
    }
};

sigarette sine( sigarette frequency );
sigarette sine( double frequency );
sigarette saw( sigarette frequency );
sigarette square( sigarette frequency );
sigarette triangle( sigarette frequency );
