#pragma once

#include "../core.h"
#include "Add.h"
#include "Multiply.h"
#include "Osc.h"

class LFO : public Patch<double>
{
private:
    // TODO: Make the waveform customisable
    std::shared_ptr<Osc>      osc        = Osc::create_sine();
    std::shared_ptr<Multiply> modulation = Multiply::create();
    std::shared_ptr<Add>      sum        = std::make_shared<Add>();

public:
    LFO()
    {
        modulation->a << osc;
        sum->b << modulation;
        exposeOutput( sum );
    }

    std::string label()
    {
        return "LFO";
    }

    FrameStreamConsumer<double>& frequency = exposeInput( osc->frequency );
    FrameStreamConsumer<double>& depth     = exposeInput( modulation->b );
    FrameStreamConsumer<double>& center    = exposeInput( sum->a );
};
