#include "../parsing/LazyRegex.h"
#include "../parsing/NumberWithUnit.h"
#include "SignalShorthands.h"
#include "signal-processes.h"
#include <memory>
#include <string>

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
        std::cerr << "Adding step " << from << " to " << to << " over " << durationinSeconds << "s\n";
        using SignalShorthands::constant;
        return addStep( constant( from ), constant( to ), durationinSeconds );
    }

    BreakpointEnvelopeSequencer& addStep( double to, double duration )
    {
        addStep( lastSignal, SignalShorthands::constant( to ), duration );
        return *this;
    }


    BreakpointEnvelopeSequencer& addStep( double to )
    {
        return addStep( lastSignal, SignalShorthands::constant( to ), lastDuration() );
    }

    BreakpointEnvelopeSequencer& addHold( double duration )
    {
        return addStep( lastSignal, lastSignal, duration );
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


using std::string;

class ControlString
{

private:
    BreakpointEnvelopeSequencer sequencer;

public:
    std::shared_ptr<Sequence> sequence()
    {
        return sequencer.sequence;
    }

public:
    class TempoInstruction
    {
    public:
        static LazyRegex pattern;

        static Hopefully<float> parse( const string& str )
        {
            if ( pattern.test( str ) )
            {
                return NumberWithUnit::parseInterval( str.substr( 0, str.size() - 1 ) );
            }
            else
                return Disappointment;
        }
    };

    class ValueInstruction
    {
    public:
        static LazyRegex pattern;

        static Hopefully<float> parse( const string& str )
        {
            if ( pattern.test( str ) )
            {
                auto nu = NumberWithUnit::parse( str );
                // TODO: Clearly this needs work
                if ( nu.success() && nu->unit == Units::noUnit )
                    return nu->number;
                else
                    return Disappointment;
            }
            else
                return Disappointment;
        }
    };

    class SustainStepInstruction
    {
    public:
        static LazyRegex pattern;

        typedef enum
        {
            Resting,
            Gliding
        } SustainKind;

        static Hopefully<SustainKind> parse( const string& str )
        {
            if ( str == "~" )
                return Gliding;
            else if ( str == "_" )
                return Resting;
            else
                return Disappointment;
        }
    };

    bool append( const string& str )
    {
        std::smatch result;
        string      remainder = str.substr( 0, str.size() );
        while ( std::regex_search( remainder, result, *firstInstructionPattern ) )
        {
            appendInstruction( result[1] );
            remainder = remainder.substr( result[0].str().size(), remainder.size() );
        }

        if ( remainder.size() == 0 )
            return true;
        else
            return false;
    }

    /**
     * returns `true` when successful.
     */
    bool appendInstruction( const string& str )
    {
        std::cerr << "Appending instruction: " << str << "\n";
        auto sustainInstruction = SustainStepInstruction::parse( str );
        if ( sustainInstruction.success() )
            return appendSustainInstruction( *sustainInstruction );

        auto tempoInstruction = TempoInstruction::parse( str );
        if ( tempoInstruction.success() )
        {
            return appendTempoInstruction( *tempoInstruction );
        }

        auto value = ValueInstruction::parse( str );
        if ( value.success() )
        {
            return appendValueInstruction( *value );
        }

        return false;
    }

private:
    struct SustainStep
    {
        double                              duration;
        SustainStepInstruction::SustainKind kind;
    };
    std::vector<SustainStep> sustainSteps;

    int countGlidingSteps()
    {
        int n = 0;
        for ( auto& step : sustainSteps )
            if ( step.kind == SustainStepInstruction::Gliding )
                ++n;
        return n;
    }

    double lastValue = 0;
    void   flushSustainSteps( double target )
    {
        const int    numberOfGlidingSteps = countGlidingSteps();
        double       y                    = lastValue;
        const double totalChange          = target - y;
        const double changePerGlidingStep = totalChange / numberOfGlidingSteps;
        for ( auto& step : sustainSteps )
        {
            if ( step.kind == SustainStepInstruction::Gliding )
            {
                sequencer.addStep( y, y + changePerGlidingStep, step.duration );
                y += changePerGlidingStep;
            }
            else
            {
                sequencer.addHold( step.duration );
            }
        }
        sustainSteps.clear();
    }

public:
    bool appendSustainInstruction( SustainStepInstruction::SustainKind sustainInstruction )
    {
        sustainSteps.push_back( { stepInterval, sustainInstruction } );
        return true;
    }

    float stepInterval = 1;
    bool  appendTempoInstruction( float interval )
    {
        stepInterval = interval;
        return true;
    }

public:
    bool appendValueInstruction( float target )
    {
        if ( sustainSteps.size() > 0 )
            flushSustainSteps( target );
        lastValue = target;
        return true;
    }

public:
    static LazyRegex anyInstructionPattern;
    static LazyRegex firstInstructionPattern;
    static LazyRegex pattern;

    static std::shared_ptr<Sequence> parse( const std::string& str )
    {
        std::shared_ptr<ControlString> instance   = std::make_shared<ControlString>();
        auto                           successful = instance->append( str );
        if ( !successful )
        {
            std::cerr << "Couldn't parse control string: \"" << str << "\"n";
            // TODO: Use proper exceptions
            throw 1;
        }

        instance->flushSustainSteps( 0 );

        return instance->sequence();
    }
};

} // namespace NaiveInstruments
