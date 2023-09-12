#include "./Signal.h"
#include "./signal-processes.h"
#include <map>
#include <memory>
#include <string>

namespace NaiveInstruments
{
class AbstractConstructor
{

public:
    const std::string shorthand;

    AbstractConstructor( const std::string shorthand )
    : shorthand( shorthand )
    {
    }

    virtual std::shared_ptr<Signal<double>> construct()      = 0;
    virtual std::string                     signaltypename() = 0;
};

template <typename T>
class SignalProcessConstructor : public AbstractConstructor
{
public:
    SignalProcessConstructor( const std::string shorthand )
    : AbstractConstructor( shorthand )
    {
    }

    std::shared_ptr<Signal<double>> construct() override
    {
        return std::make_shared<T>();
    }

    std::string signaltypename() override
    {
        return typeid( T ).name();
    }
};

class SignalProcessConstructorGroup
{
private:
    std::map<std::string, AbstractConstructor*> map;

protected:
    void add( AbstractConstructor* constructor )
    {
        map[constructor->shorthand] = constructor;
    }

    void add( AbstractConstructor& constructor )
    {
        add( &constructor );
    }

public:
    std::shared_ptr<Signal<double>> construct( std::string shorthand )
    {
        if ( map.contains( shorthand ) )
            return map[shorthand]->construct();
        else
        {
            std::cerr << "No signal process defined for shorthand: " << shorthand << "\n";
            // TODO: Use expections properly!
            throw 1;
        }
    }

    std::string recognise( std::shared_ptr<Signal<double>> signal )
    {
        auto name = typeid( *signal ).name();
        for ( auto const& x : map )
        {
            if ( name == x.second->signaltypename() )
                return x.second->shorthand;
        }
        return "?";
    }
};

class StandardSignalConstructor : public SignalProcessConstructorGroup
{
public:
    StandardSignalConstructor()
    : SignalProcessConstructorGroup()
    {
        add( noise );
        add( usaw );
        add( sum );
        add( subtract );
        add( signFlip );
        add( multiply );
        add( divide );
        add( repeater );
        add( clock );
        add( accumulator );
        add( modulo );
        add( noise );
        add( hardClip );
        add( linearRamp );
        add( sequence );
    }

    SignalProcessConstructor<USaw>             usaw{ "usaw" };
    SignalProcessConstructor<Sum<double>>      sum{ "sum" };
    SignalProcessConstructor<Subtract<double>> subtract{ "subtract" };
    SignalProcessConstructor<SignFlip>         signFlip{ "signFlip" };
    SignalProcessConstructor<Multiply>         multiply{ "multiply" };
    SignalProcessConstructor<Divide>           divide{ "divide" };
    // TODO: Support stereo
    /* SignalProcessConstructor<MonoToStereo>     monoToStereo{ "monoToStereo" }; */
    /* SignalProcessConstructor<StereoChannels>   stereoChannels{ "stereoChannels" }; */
    /* SignalProcessConstructor<Pan>              pan{ "pan" }; */
    SignalProcessConstructor<Repeater<double>> repeater{ "repeater" };
    SignalProcessConstructor<Clock<double>>    clock{ "clock" };
    SignalProcessConstructor<Accumulator>      accumulator{ "accumulator" };
    SignalProcessConstructor<Modulo>           modulo{ "modulo" };
    SignalProcessConstructor<Noise>            noise{ "noise" };
    /* SignalProcessConstructor<Sampler>          sampler{ "sampler" }; */
    /* SignalProcessConstructor<Wavetable>        wavetable{ "wavetable" }; */
    /* SignalProcessConstructor<Wait<double>> wait{ "wait" }; */
    /* SignalProcessConstructor<Skip<double>> skip{ "skip" }; */
    /* SignalProcessConstructor<Elapse<double>>   elapse{ "elapse" }; */
    SignalProcessConstructor<IntervalToRatio> intervalToRatio{ "intervalToRatio" };
    /* SignalProcessConstructor<BufferLooper>     bufferLooper{ "bufferLooper" }; */
    SignalProcessConstructor<HardClip<double>> hardClip{ "hardClip" };
    SignalProcessConstructor<LinearRamp>       linearRamp{ "linearRamp" };
    SignalProcessConstructor<Sequence>         sequence{ "sequence" };
    /* SignalProcessConstructor<FixedDelay>       fixedDelay{ "fixedDelay" }; */
};
} // namespace NaiveInstruments
