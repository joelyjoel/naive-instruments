#pragma once

#include "../core.h"

class IntervalToRatio : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> interval{ this, "interval/st" };

    static std::shared_ptr<IntervalToRatio> create()
    {
        return std::make_shared<IntervalToRatio>();
    }

    std::string label() override
    {
        return "IntervalToRatio";
    }

protected:
    void action() override
    {
        output[0] = pow( 2.0, ( interval.readFrame() / 12.0 ) );
    }
};

std::shared_ptr<IntervalToRatio> intervalToRatio( std::shared_ptr<FrameStream<double>> intervalSignal )
{
    auto converter = IntervalToRatio::create();
    converter->interval << intervalSignal;
    return converter;
}

class PitchConverter : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> pitch{ this, "pitch/MIDI" };

    static std::shared_ptr<PitchConverter> create()
    {
        return std::make_shared<PitchConverter>();
    }

    std::string label() override
    {
        return "PitchConverter";
    }

private:
    void action() override
    {
        output[0] = 440 * pow( 2.0, ( ( pitch.readFrame() - 69 ) / 12.0 ) );
    }
};

std::shared_ptr<PitchConverter> pitchToFrequency( std::shared_ptr<FrameStream<double>> pitchSignal )
{
    auto converter = PitchConverter::create();
    converter->pitch << pitchSignal;
    return converter;
}
