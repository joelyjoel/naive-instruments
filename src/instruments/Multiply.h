#pragma once

#include "../core.h"

class Multiply : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> a{ this, "a" };
    FrameStreamConsumer<double> b{ this, "a" };

protected:
    void action() override
    {
        output[0] = a.readFrame() * b.readFrame();
    }

public:
    std::string label() override
    {
        return "Multiply";
    }

    static std::shared_ptr<Multiply> create()
    {
        return std::make_shared<Multiply>();
    }
};

/**
 * Mix an additional signal into a input
 */
void operator*=( FrameStreamConsumer<double>& signalInput, std::shared_ptr<FrameStream<double>> additionalSignal );

std::shared_ptr<FrameStream<double>> operator*( std::shared_ptr<FrameStream<double>> a,
                                                std::shared_ptr<FrameStream<double>> b );
