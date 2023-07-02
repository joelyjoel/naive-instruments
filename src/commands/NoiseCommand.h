// The first thing we do here is to include the library, to make all the
// classes available:
#include "../lib.h"

// Next we declare a class which extends the `AudioCommand` base class. This
// has helpful methods for command line options, audio input/output from
// streams and sending audio to the speakers.
class NoiseCommand : public AudioCommand
{
public:
    // We have to manually add the class constructor from the base class. This is
    // some boilerplate code that I hope to eliminate the need for soon.
    using AudioCommand::AudioCommand;

protected:
    // By overriding the `describeOptions` we declare how the user may configure
    // this command using optstrings.
    //
    // Helpful video about command line tools:
    // https://www.youtube.com/watch?v=kgII-YWo3Zw&t=1225s
    void describeOptions() override
    {

        // This helpful method sets up the standard options used by the `output`
        // method later on. Allows the user to use the `-o <output-file>.wav` to
        // send audio to a file, or pipe the WAV output to stdout.
        describeOutputOptions();
    }

protected:
    // We define the actual signal processing part of our command by overriding
    // the `action` method.
    void action() override
    {

        auto noise = NaiveInstruments::SignalShorthands::noise();

        // We send our signal straight to the output. The `output` method will work
        // out where to send the audio depending on the user's command line options.
        output( noise );
    }
};
