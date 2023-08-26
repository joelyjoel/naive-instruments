#include "../signal/SignalShorthands.h"
#include "Random.h"
#include <functional>
#include <map>

namespace NaiveInstruments
{

typedef std::function<std::shared_ptr<Signal<double>>()> Generator;

class RandomSignal
{

    std::map<std::string, Generator> map;

    Random random;

public:
    RandomSignal()
    {
        using namespace NaiveInstruments::SignalShorthands;
        map["frequency"] = [this]() { return constant( this->random( 20, 20000 ) ); };
        map["sine_wave"] = [this]() { return sine( this->create( "frequency" ) ); };
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> create( std::string shorthand )
    {
        return map[shorthand]();
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> operator()( std::string shorthand )
    {
        return create( shorthand );
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> boop()
    {
        using namespace NaiveInstruments::SignalShorthands;
        return decay( this->random( .2, 2 ) ) * create( "sine" );
    }
};

} // namespace NaiveInstruments
