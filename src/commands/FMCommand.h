#include "../lib.h"

class FMCommand : public CommandLineApp
{

    using CommandLineApp::CommandLineApp;

public:
    void run()
    {
        int numberOfOscs = args.numberOfPositionalArgs();

        // Create the oscs
        std::vector<shared_ptr<Osc>>                 oscs;
        std::vector<shared_ptr<FrameStream<double>>> outputs;

        for ( int i = 0; i < numberOfOscs; ++i )
        {
            shared_ptr<Osc> osc = Osc::create_sine();
            oscs.push_back( osc );
            const std::string key = std::to_string( i );
            if ( args.exists( key ) )
                outputs.push_back( osc * args.signal( key ) );
            else
                outputs.push_back( osc );
        }

        // Assign the fundamental frequencies
        shared_ptr<FrameStream<double>> fundamentalPitch     = SignalString::parse( args[0] );
        shared_ptr<PitchConverter>      fundamentalFrequency = pitchToFrequency( fundamentalPitch );
        for ( int i = 0; i < numberOfOscs; ++i )
        {
            shared_ptr<Osc> osc = oscs[i];

            if ( i == 0 )
            {
                osc->frequency << fundamentalFrequency;
            }
            else
            {
                shared_ptr<FrameStream<double>> ratio = SignalString::parse( args[i] );
                osc->frequency << fundamentalFrequency * ratio;
            }
        }

        // TODO: Add modulation routings
        for ( int carrierIndex = 0; carrierIndex < numberOfOscs; ++carrierIndex )
        {
            for ( int modulatorIndex = 0; modulatorIndex < numberOfOscs; ++modulatorIndex )
            {
                const std::string key = std::to_string( modulatorIndex ) + "to" + std::to_string( carrierIndex );
                if ( args.exists( key ) )
                {
                    shared_ptr<FrameStream<double>> modulation = args.signal( key );

                    shared_ptr<IntervalToRatio> ratio = intervalToRatio( outputs[modulatorIndex] * modulation );
                    oscs[carrierIndex]->frequency *= ratio;
                }
            }
        }

        // Create the final mix
        shared_ptr<FrameStream<double>> mixdown;
        for ( int i = 0; i < numberOfOscs; ++i )
        {
            shared_ptr<FrameStream<double>> oscOutput = outputs[i];
            const std::string               key       = std::to_string( i ) + "-out";
            if ( args.exists( key ) || i == 0 )
            {
                shared_ptr<FrameStream<double>> level = args.signal( key, i == 0 ? "1" : "0" );

                if ( mixdown == nullptr )
                    mixdown = oscOutput * level;
                else
                    mixdown = mixdown + ( oscOutput * level );
            }
        }

        if ( mixdown != nullptr )
            output( *mixdown );
        else
            std::cerr << "Mixdown is null\n";
    }
};
