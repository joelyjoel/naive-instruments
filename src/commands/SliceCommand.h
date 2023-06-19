#include "../lib.h"

class SliceCommand : public CommandLineApp
{
    using CommandLineApp::CommandLineApp;

public:
    void run()
    {
        MonoBuffer* buffer = mainInputAsBuffer();

        // TODO: support time units: s, samp, zx, onset etc
        const float from = args.number( "from", 0 );
        const float to   = args.number( "to", buffer->duration() );

        MonoBuffer* sliced = buffer->slice( from, to );

        // TODO: refactor using move semantics
        const float numberOfRepetitions = args.number( "repeat", 1 );
        if ( numberOfRepetitions != 1 )
        {
            std::cerr << "repeating\n";
            auto repeated = sliced->repeat( numberOfRepetitions );
            delete sliced;
            sliced = repeated;
            // TODO: Configurable crossfades
        }

        const float fadeIn = args.number( "fadeIn", 0.005 );
        sliced->fadeIn( fadeIn );

        const float fadeOut = args.number( "fadeOut", 0.005 );
        sliced->fadeOut( fadeOut );

        const float fade = args.number( "fade", 0 );
        sliced->fadeBoth( fade );

        // TODO: --loopUntil duration (overrides repeat)
        // TODO: --after - adding silence before the sample

        output( sliced );
    }
};
