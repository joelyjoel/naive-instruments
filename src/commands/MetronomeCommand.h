#include "../lib.h"


namespace NaiveInstruments
{

class MetronomeCommand : public AudioCommand
{

    using AudioCommand::AudioCommand;

    void describeOptions() override
    {
        describeOutputOptions();
        options.add_options()( "bpm,beats-per-minute",
                               po::value<double>()->default_value( 139 ),
                               "What beats per minute should the metronome play" )(
            "pattern", po::value<vector<string>>(), "Binary rhythmic pattern" );
    }

    void action() override
    {
        using namespace SignalShorthands;

        auto bpm = args["bpm"].as<double>();

        vector<mono> tracks;

        const vector<string>& patternStrings =
            args.count( "pattern" ) ? args["pattern"].as<vector<string>>() : vector<string>( { "1000" } );

        for ( int i = 0; i < patternStrings.size(); ++i )
        {
            const string& patternStr = patternStrings[i];

            auto boop = sine( ( i + 1 ) * 500.0 ) * decay( .1 );

            auto  durationPattern = RhythmString::parse( patternStr );
            float stepDuration    = 60.0 / bpm / 2;
            for ( float& step : durationPattern )
                step *= stepDuration;

            tracks.push_back( repeatedSound( boop, durationPattern ) );
        }

        output( add( tracks ) / tracks.size() );
    }
};

} // namespace NaiveInstruments
