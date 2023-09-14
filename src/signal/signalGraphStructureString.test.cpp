#include "./signalGraphStructureString.h"
#include "../test-framework/custom-assertions.h"
#include "SignalShorthands.h"

using namespace NaiveInstruments;
using namespace SignalShorthands;

TEST_CASE( "Can generate structure string for many kinds of signals without crashing" )
{
    auto signal = GENERATE(
        constant( 2 ), sine( 440 ), step_sequence( 60, { sine( 440 ), square( constant( 200 ) * decay( .4 ) ) } ) );
    INFO( typeid( *signal ).name() );
    std::string str = SignalGraph::signalGraphStructureString( signal );
}
