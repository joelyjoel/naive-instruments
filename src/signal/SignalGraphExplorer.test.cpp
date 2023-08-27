#include "./SignalGraphExplorer.h"
#include "../test-framework/custom-assertions.h"
#include "./SignalShorthands.h"

using namespace NaiveInstruments;
using namespace SignalShorthands;

TEST_CASE( "Listing the direct inputs of a signal" )
{
    auto mySum = std::make_shared<Sum<double>>();

    CHECK( SignalGraphExplorer::directSignalInputs( mySum ).size() == 0 );

    mySum->input1 = sine( 440 );
    CHECK( SignalGraphExplorer::directSignalInputs( mySum ).size() == 1 );
    mySum->input2 = sine( 440 );
    CHECK( SignalGraphExplorer::directSignalInputs( mySum ).size() == 2 );
}

TEST_CASE( "Recursively listing the signals which are an input to the given signal" )
{
    auto signal = noise() + noise() + noise();

    auto allProcesses = SignalGraphExplorer::recursiveSignalInputs( signal, true );
    CHECK( allProcesses.size() == 5 );
}

TEST_CASE( "Finding unassigned inputs" )
{
    auto signal = noise() + noise() + noise();
    CHECK( SignalGraphExplorer::recursivelyListUnassignedAccessors( signal ).size() == 0 );

    auto mySum = std::make_shared<Sum<double>>();
    signal     = noise() + noise() + mySum;
    CHECK( SignalGraphExplorer::recursivelyListUnassignedAccessors( signal ).size() == 2 );
}
