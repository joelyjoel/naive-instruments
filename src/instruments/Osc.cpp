#include "Osc.h"

sigarette sine( sigarette frequency )
{
    auto osc = Osc::create( Waveforms::sine() );
    osc->frequency << frequency;
    return osc;
}

sigarette sine( double frequency )
{
    auto osc = Osc::create( Waveforms::sine() );
    osc->frequency << frequency;
    return osc;
}

sigarette saw( sigarette frequency )
{
    auto osc = Osc::create( Waveforms::saw() );
    osc->frequency << frequency;
    return osc;
}

sigarette square( sigarette frequency )
{
    auto osc = Osc::create( Waveforms::square() );
    osc->frequency << frequency;
    return osc;
}

sigarette triangle( sigarette frequency )
{
    auto osc = Osc::create( Waveforms::triangle() );
    osc->frequency << frequency;
    return osc;
}
