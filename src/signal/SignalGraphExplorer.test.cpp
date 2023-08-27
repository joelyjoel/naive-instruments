#include "./SignalGraphExplorer.h"
#include "../test-framework/custom-assertions.h"
#include "./SignalShorthands.h"

TEST_CASE( "Listing the direct inputs of a signal" )
{
    using namespace NaiveInstruments;
    using namespace SignalShorthands;
    auto mySum = std::make_shared<Sum<double>>();

    CHECK( SignalGraphExplorer::directSignalInputs( mySum ).size() == 0 );

    mySum->input1 = sine( 440 );
    CHECK( SignalGraphExplorer::directSignalInputs( mySum ).size() == 1 );
    mySum->input2 = sine( 440 );
    CHECK( SignalGraphExplorer::directSignalInputs( mySum ).size() == 2 );
}
