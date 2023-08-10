#include "../lib.h"

class ZxSelectCommand : public CommandLineApp
{
public:
    using CommandLineApp::CommandLineApp;

    void run() override
    {
        const std::string& outputPath = args["o"];
        bool               normalize  = args.boolean( "normalize" );
        std::cerr << "Normalize: " << normalize << "\n";

        auto                     inputBuffer = mainInputAsBuffer();
        std::shared_ptr<Sampler> sampler     = make_shared<Sampler>( inputBuffer );
        WaveformBufferer         bufferer;
        bufferer.minNumberOfFrames = args.integer( "min-frames", 100 );

        bufferer << sampler;

        auto indexToSelect = args.requireInt( "index" );

        auto waveform = bufferer[indexToSelect];

        output( waveform );
    }
};
