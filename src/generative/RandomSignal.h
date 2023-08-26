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
        // sounds
        map["tone"]          = [this]() { return create( random( { "sine_wave", "square_wave", "triangle_wave" } ) ); };
        map["sine_wave"]     = [this]() { return sine( create( "frequency" ) ); };
        map["square_wave"]   = [this]() { return square( create( "frequency" ) ); };
        map["sawtooth_wave"] = [this]() { return saw( create( "frequency" ) ); };
        map["triangle_wave"] = [this]() { return triangle( create( "frequency" ) ); };

        map["boop"]      = [this]() { return decay( create( "duration" ) ) * create( "tone" ); };
        map["sine_boop"] = [this]() { return decay( create( "duration" ) ) * create( "tone" ); };

        // Control signals
        map["duration"]        = [this]() { return constant( random( .1, 4 ) ); };
        map["attack_envelope"] = [this]() { return attack( create( "duration" ) ); };
        map["decay_envelope"]  = [this]() { return decay( create( "duration" ) ); };
        map["frequency"]       = [this]() { return midiPitch( create( "pitch" ) ); };
        map["constant_pitch"]  = [this]() { return constant( random( 20, 108 ) ); };
        map["sliding_pitch"] = [this]() { return ramp( create( "pitch" ), create( "duration" ), create( "pitch" ) ); };
        map["pitch"]         = [this]() { return create( random( { "constant_pitch", "sliding_pitch" } ) ); };
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> create( std::string shorthand )
    {
        if ( map.contains( shorthand ) )
            return map[shorthand]();
        else
        {
            std::cerr << "Unexpected shorthand: " << shorthand << "\n";
            throw 1;
        }
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> create( const std::vector<std::string>& shorthandOptions )
    {
        return create( random( shorthandOptions ) );
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> operator()( std::string shorthand )
    {
        return create( shorthand );
    }

    std::shared_ptr<NaiveInstruments::Signal<double>> boop()
    {
    }
};

} // namespace NaiveInstruments
