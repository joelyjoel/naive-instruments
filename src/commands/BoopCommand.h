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
        using namespace NaiveInstruments::SignalShorthands;
        MonoBuffer* table = inputWaveform();

        mono frequency = inputFrequency();
        mono envelope  = decay( inputDuration() );


        auto signal = envelope * oscWithWavetable( table, frequency );

        output( signal );
    }
};
