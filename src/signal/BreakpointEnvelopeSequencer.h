#include "SignalShorthands.h"
#include "signal-processes.h"
#include <memory>

namespace NaiveInstruments
{


/**
 * Sometimes we want to sequence a breakpoint envelope one step at a time. For example when interpretting a control
 * signal string. This is a class to help with that.
 */
class BreakpointEnvelopeSequencer
{
public:
    std::shared_ptr<Sequence> sequence;

    BreakpointEnvelopeSequencer()
    {
        sequence = std::make_shared<Sequence>();
    }


private:
    SignalShorthands::mono lastSignal = SignalShorthands::constant( 0 );

public:
    BreakpointEnvelopeSequencer& addStep( SignalShorthands::mono from,
                                          SignalShorthands::mono to,
                                          double                 durationInSeconds )
    {
        auto slide = SignalShorthands::ramp( from, durationInSeconds, to );
        // TODO: Shouldn't use inline constant for sample rate
        // TODO: I don't like that we are mixing units for durations in this class
        sequence->addStep( durationInSeconds * 44100, slide );
        lastSignal = to;
        return *this;
    }

    BreakpointEnvelopeSequencer& addStep( double from, double to, double durationinSeconds )
    {
        using SignalShorthands::constant;
        addStep( constant( from ), constant( to ), durationinSeconds );
        return *this;
    }

    BreakpointEnvelopeSequencer& addStep( double to, double duration )
    {
        addStep( lastSignal, SignalShorthands::constant( to ), duration );
        return *this;
    }


    BreakpointEnvelopeSequencer& addStep( double to )
    {
        addStep( lastSignal, SignalShorthands::constant( to ), lastDuration() );
        return *this;
    }

    double lastDuration()
    {
        if ( sequence->numberOfSteps() == 0 )
            // TODO: Use proper exceptions
            throw 1;
        // TODO: Shouldn't use inline constant for sample rate
        // TODO: I don't like that we are mixing units for durations in this class
        return sequence->lastStep().duration / 44100.0;
    }
};
} // namespace NaiveInstruments
