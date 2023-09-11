#include "WavWriter.h"
#include "../signal/SignalShorthands.h"
#include "../test-framework/custom-assertions.h"

using namespace NaiveInstruments::SignalShorthands;

TEST_CASE( "Recording a stereo signal using WavWriter" )
{
    auto signal = stereoChannels( sine( 440 ), sine( 300 ) );
    referenceToneTest( "440Hz stereo sine.wav", signal );
}
