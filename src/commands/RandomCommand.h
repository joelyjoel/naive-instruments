#include "../generative/Random.h"
#include "../generative/RandomSignal.h"
#include "../lib.h"
#include "./RandomEnvelopeCommand.h"

class RandomCommand : public AudioCommand
{

    using AudioCommand ::AudioCommand;

public:
    void describeOptions() override
    {
        options.add_options()(
            "command", po::value<std::string>(), "What kind of data would you like to randomly generate?" )(
            "seed", po::value<long>() )( "min", po::value<float>(), "Minimum, when generating random numeric data" )(
            "max", po::value<float>(), "Maximum, when generating random numeric data" );
        positionalOptions.add( "command", 1 );
        describeOutputOptions();
    }

    void action() override
    {

        if ( !args.count( "command" ) )
        {
            std::cerr << "A random what?\n";
            NaiveInstruments::RandomSignal r( seed() );
            auto                           availableCommands = r.availableCommands();
            for ( auto command : availableCommands )
                std::cerr << " - " << command << "\n";
            return;
        }
        const std::string& command = args["command"].as<std::string>();

        try
        {
            NaiveInstruments::RandomSignal r( seed() );
            auto                           signal = r.create( command );
            output( signal );
            return;
        }
        catch ( ... )
        {
            // noop
        }

        if ( command == "envelope" )
        {
            MainArgs              subArgs = subCommandArguments();
            RandomEnvelopeCommand app( subArgs );
            app.run();
        }
        else if ( command == "frequency" )
            frequency();
        else if ( command == "pitch" )
            pitch();
        else
            std::cerr << "Unexpected sub-command: " << command << "\n";
    }

private:
    uint64_t seed()
    {
        if ( args.count( "seed" ) )
            return args["seed"].as<long>();
        else
            return Random::clockSeed();
    }

    Random random = seed();

    void frequency()
    {
        double min = args.count( "min" ) ? args["min"].as<float>() : 20;
        double max = args.count( "max" ) ? args["max"].as<float>() : 20000;
        std::cout << random.number( min, max ) << "Hz\n";
    }

    void pitch()
    {
        double min = args.count( "min" ) ? args["min"].as<float>() : 20;
        double max = args.count( "max" ) ? args["max"].as<float>() : 108;
        std::cout << random.number( min, max ) << "MIDI\n";
    }
};
