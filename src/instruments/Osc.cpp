#include "Osc.h"

std::shared_ptr<FrameStream<double>> sine( std::shared_ptr<FrameStream<double>> frequency )
{
    auto osc = Osc::create( Waveforms::sine() );
    osc->frequency << frequency;
    return osc;
}

std::shared_ptr<FrameStream<double>> sine( double frequency )
{
    auto osc = Osc::create( Waveforms::sine() );
    osc->frequency << frequency;
    return osc;
}

std::shared_ptr<FrameStream<double>> saw( std::shared_ptr<FrameStream<double>> frequency )
{
    auto osc = Osc::create( Waveforms::saw() );
    osc->frequency << frequency;
    return osc;
}

std::shared_ptr<FrameStream<double>> square( std::shared_ptr<FrameStream<double>> frequency )
{
    auto osc = Osc::create( Waveforms::square() );
    osc->frequency << frequency;
    return osc;
}

std::shared_ptr<FrameStream<double>> triangle( std::shared_ptr<FrameStream<double>> frequency )
{
    auto osc = Osc::create( Waveforms::triangle() );
    osc->frequency << frequency;
    return osc;
}
