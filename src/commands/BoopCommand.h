#include "../lib.h"

class BoopCommand : public AudioCommand
{
    using AudioCommand::AudioCommand;

    void describeOptions() override
    {
        addWaveformOptions();
        addPitchOptions();
        describeOutputOptions();
    }

    void action() override
    {
        MonoBuffer&                     waveform       = *inputWaveform();
        std::shared_ptr<Osc>            osc            = std::make_shared<Osc>( waveform );
        std::shared_ptr<PitchConverter> pitchConverter = std::make_shared<PitchConverter>();

        std::shared_ptr<FrameStream<double>> frequency = inputFrequency();
        std::shared_ptr<Decay>               envelope  = std::make_shared<Decay>();

        envelope->duration << inputDuration();

        osc->frequency << frequency;

        output( ( osc * envelope ) );
    }
};
