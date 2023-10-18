#include "../instruments/ControlString.h"
#include "../lib.h"
#include <iostream>

class OscCommand : public AudioCommand
{
    using AudioCommand::AudioCommand;

    void describeOptions() override
    {
        describeOutputOptions();
        options.add_options()( "pitch",
                               po::value<double>()->default_value( 50.0 ),
                               "Frequency of the oscillator expressed as a midi pitch number." );
        addWaveformOptions();
        addVibratoOptions();
        options.add_options()(
            "volume", po::value<double>()->default_value( 1.0 ), "Output level of the oscillator from 0-1" );
    }

public:
    void action() override
    {

        MonoBuffer&                     waveform       = *inputWaveform();
        std::shared_ptr<Osc>            osc            = std::make_shared<Osc>( waveform );
        std::shared_ptr<PitchConverter> pitchConverter = std::make_shared<PitchConverter>();
        std::shared_ptr<Multiply>       gain           = std::make_shared<Multiply>();
        std::shared_ptr<Add>            pitchSum       = std::make_shared<Add>();

        std::shared_ptr<LFO> vibrato = std::make_shared<LFO>();

        /* const std::string str = args[0]; */
        /* auto &f = **ControlString::parse(str); */

        std::shared_ptr<FrameStream<double>> pitch = inputPitch();

        vibrato->depth << args["vibrato-amount"].as<double>();
        vibrato->frequency << args["vibrato-frequency"].as<double>();
        pitchSum->a << pitch;
        pitchSum->b << vibrato;
        pitchConverter->pitch << pitchSum;
        osc->frequency << pitchConverter;
        gain->a << osc;
        gain->b << args["volume"].as<double>();

        output( gain );
    }
};
