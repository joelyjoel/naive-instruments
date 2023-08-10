#include "../lib.h"

class FilterCommand : public AudioCommand
{
    using AudioCommand::AudioCommand;

    void describeOptions() override
    {
        describeOutputOptions();
        options.add_options()( "frequency", po::value<std::string>(), "Cut or central frequency for the filter" )(
            "pitch",
            po::value<std::string>(),
            "Define the cut off frequency (or central frequency) using a "
            "midi number" )( "high-pass,hp", "Use a high-pass filter" )( "band-pass,bp", "Use a band pass filter" )(
            "band-reject,br", "Use a band-reject filter" )( "low-pass,lp", "Use a low-pass filter" );

        // TODO: Add bandwidth
    }

public:
    void action() override
    {
        // TODO: This needs to be shared too
        auto input = inputAsBuffer();

        std::shared_ptr<Sampler>           sampler = make_shared<Sampler>( input );
        std::shared_ptr<ButterworthFilter> filter  = std::make_shared<ButterworthFilter>();

        filter->kind = getFilterKind();

        filter->input << sampler;

        if ( args.count( "frequency" ) )
        {
            std::shared_ptr<FrameStream<double>> frequency = SignalString::parse( args["frequency"].as<std::string>() );
            filter->frequency << frequency;
            output( filter );
        }
        else if ( args.count( "pitch" ) )
        {
            std::shared_ptr<PitchConverter>      pitchConverter = std::make_shared<PitchConverter>();
            std::shared_ptr<FrameStream<double>> pitch = SignalString::parse( args["pitch"].as<std::string>() );
            pitchConverter->pitch << pitch;
            filter->frequency << pitchConverter;
            output( filter );
        }
        else
        {
            std::cerr << "No --frequency or --pitch specified\n";
            throw 1;
        }
    }

    ButterworthFilter::FilterKind getFilterKind()
    {
        if ( args.count( "high-pass" ) )
            return ButterworthFilter::HighPass;
        else if ( args.count( "band-pass" ) )
            return ButterworthFilter::BandPass;
        else if ( args.count( "band-reduce" ) )
            return ButterworthFilter::BandReduce;
        else if ( args.count( "low-pass" ) )
            return ButterworthFilter::LowPass;
        else
            return ButterworthFilter::LowPass;
    }
};
