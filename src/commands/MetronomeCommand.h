#include "../lib.h"

class MetronomeCommand : public AudioCommand
{

    using AudioCommand::AudioCommand;

    void describeOptions() override
    {
        describeOutputOptions();
        options.add_options()( "bpm,beats-per-minute",
                               po::value<string>()->default_value( "139" ),
                               "What beats per minute should the metronome play" )(
            "pattern", po::value<vector<string>>(), "Binary rhythmic pattern" );
    }

    void action() override
    {

        std::shared_ptr<FrameStream<double>>         bpm = SignalString::parse( args["bpm"].as<string>() );
        vector<std::shared_ptr<FrameStream<double>>> tracks;
        const vector<string>&                        patternStrings =
            args.count( "pattern" ) ? args["pattern"].as<vector<string>>() : vector<string>( { "10" } );

        for ( int i = 0; i < patternStrings.size(); ++i )
        {
            const string& patternStr = patternStrings[i];

            std::shared_ptr<FrameStream<double>> osc        = sine( ( i + 1 ) * 500.0 );
            std::shared_ptr<ControlString>       envelope   = *ControlString::parse( "100ms:1~0" );
            std::shared_ptr<FrameStream<double>> attenuator = osc * envelope;

            cerr << "Pattern: " << patternStr << "\n";
            std::shared_ptr<Rhythm> rhythm = Rhythm::parse( patternStr );
            rhythm->bpm << bpm;
            cerr << *rhythm << "\n";
            std::shared_ptr<Resetter> resetter = Resetter::create();
            resetter->input << attenuator;
            resetter->trigger << rhythm;

            tracks.push_back( resetter );
        }

        output( Add::many( tracks ) );
    }
};
