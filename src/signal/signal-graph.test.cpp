#include "./signal-graph.h"
#include "../test-framework/custom-assertions.h"

TEST_CASE( "scratch" )
{
    using namespace NaiveInstruments::SignalShorthands;
    std::cerr << bracket_signal_graph( constant( 10 ) ) << "\n";
    std::cerr << bracket_signal_graph( sine( 440 ) + saw( constant( 100 ) ) ) << "\n";
}
