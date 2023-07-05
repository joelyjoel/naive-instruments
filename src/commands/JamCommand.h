#include "../SignalShorthands.h"
#include "../lib.h"


using namespace NaiveInstruments::SignalShorthands;

class JamCommand : public AudioCommand
{
public:
    using AudioCommand::AudioCommand;

    void describeOptions() override
    {
        describeOutputOptions();
    }

    void action() override
    {
        output( sine( constant( 440 ) ) );
    }
};
