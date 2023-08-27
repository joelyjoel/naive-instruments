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
    }

    SignalProcessConstructor<Noise>       noise{ "noise" };
    SignalProcessConstructor<USaw>        usaw{ "usaw" };
    SignalProcessConstructor<Sum<double>> sum{ "sum" };
};
} // namespace NaiveInstruments
