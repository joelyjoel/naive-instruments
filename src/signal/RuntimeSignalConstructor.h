#include "SignalShorthands.h"

#include <map>
#include <memory>
#include <string>


class AbstractSignalConstructor
{
public:
    virtual std::shared_ptr<NaiveInstruments::Signal<double>> construct() = 0;
};

template <typename T>
class SimpleSignalConstructor : public AbstractSignalConstructor
{
public:
    std::shared_ptr<NaiveInstruments::Signal<double>> construct()
    {
        return std::make_shared<T>();
    }
};

class SignalShorthander
{
public:
    // BUG: Memory leak here with the pointers!!
    std::map<std::string, AbstractSignalConstructor*> map;

    SignalShorthander* add( std::string shorthand, AbstractSignalConstructor* constructor )
    {
        map[shorthand] = constructor;
        return this;
    }

    template <typename T>
    SignalShorthander* add( std::string shorthand )
    {
        add( shorthand, new SimpleSignalConstructor<T> );
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> construct( std::string shorthand )
    {
        return map[shorthand]->construct();
    }


    std::shared_ptr<NaiveInstruments::Signal<double>> operator()( std::string shorthand )
    {
        return construct( shorthand );
    }
};

class StandardSignalShorthands : public SignalShorthander
{
public:
    StandardSignalShorthands()
    {
        using namespace NaiveInstruments;
        add<USaw>( "usaw" );
        add<Sum<double>>( "+" );
        add<Subtract<double>>( "-" );
    }
};
