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
    std::map<std::string, AbstractSignalConstructor*> map;

    SignalShorthander* add( std::string shorthand, AbstractSignalConstructor* constructor )
    {
        map[shorthand] = constructor;
        return this;
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
        add( "usaw", new SimpleSignalConstructor<USaw> );
        add( "+", new SimpleSignalConstructor<Sum<double>> );
        add( "-", new SimpleSignalConstructor<Subtract<double>> );
    }
};
