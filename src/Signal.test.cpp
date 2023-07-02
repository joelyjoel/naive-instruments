#include "./Signal.h"
#include "test-framework/custom-assertions.h"
#include <memory>

// TODO: Move the tests that depend on this to the right test file!
#include "./signal-processes.h"

using namespace NaiveInstruments;

TEST_CASE( "Overload Signal, instantiate and check that syncing advances the clock" )
{
    class PowersOfTwo : public Signal<double>
    {
    public:
        PowersOfTwo()
        {
            output = 1;
        }
        void action() override
        {
            // No-op
            output *= 2;
        }
    };

    PowersOfTwo a;
    a.sync( 9 );
    REQUIRE( a.t == 9 );
    REQUIRE( a.output == 512 );


    // TODO: Should assert behaviour for syncing backwards. What should that be?
}

TEST_CASE( "Check that CHECK_SIGNAL works for happy case" )
{
    auto signal    = std::make_shared<Signal<double>>();
    signal->output = 10;
    CHECK_SIGNAL<double>( signal, { 10, 10, 10, 10 } );
}

// TODO: Check that CHECK_SIGNAL fails correctly

TEST_CASE( "Accessing a signal using a SignalReader" )
{
    SignalReader<int> clockReader;
    clockReader = std::make_shared<Clock<int>>();

    REQUIRE( clockReader[0] == 0 );
    REQUIRE( clockReader[1] == 1 );
    REQUIRE( clockReader[100] == 100 );
}

TEST_CASE( "CHECK_SIGNAL works for other types of signals" )
{
    auto clock = std::make_shared<Clock<int>>();
    CHECK_SIGNAL<int>( clock, { 0, 1, 2, 3, 4 } );
}

TEST_CASE( "Instantiating constant signals" )
{
    Signal<double> a;
    a.output = 10.0;
    REQUIRE( a.t == 0 );
    REQUIRE( a.output == 10 );
    a.sync( 1 );
}

TEST_CASE( "Assigning constant signal to a signal reader, and then reading from it" )
{
    SignalReader<double> myReader;
    myReader = 10;
    REQUIRE( myReader[1] == 10 );
    REQUIRE( myReader[3] == 10 );
    myReader = 20;
    REQUIRE( myReader[10] == 20 );
}

TEST_CASE( "Assigning non constant signal to a signal reader" )
{
    auto              clock = std::make_shared<Clock<int>>();
    SignalReader<int> reader;
    reader = clock;
    REQUIRE( reader[1] == 1 );
    REQUIRE( reader[22] == 22 );
}

TEST_CASE( "Assigning a constant signal to a signal reader member on another signal" )
{

    auto repeater   = std::make_shared<Repeater<double>>();
    repeater->input = 10;
    repeater->sync( 1 );
    REQUIRE( repeater->output == 10 );
}

TEST_CASE( "Assigning a non constant signal to a signal reader member on another signal" )
{
    auto clock      = std::make_shared<Clock<int>>();
    auto repeater   = std::make_shared<Repeater<int>>();
    repeater->input = clock;
    repeater->sync( 1 );
    REQUIRE( repeater->output == 1 );
    repeater->sync( 20 );
    REQUIRE( repeater->output == 20 );
}


TEST_CASE( "Adding constant signals together" )
{
    auto add    = std::make_shared<Sum<double>>();
    add->input1 = 100;
    add->input2 = 22;
    add->sync( 1 );
    REQUIRE( add->output == 122 );
}

TEST_CASE( "A constant -> accumulator is like a clock" )
{
    auto accumulator   = std::make_shared<Accumulator>();
    accumulator->input = 1;
    accumulator->sync( 2 );
    REQUIRE( accumulator->output == 2 );
}

TEST_CASE( "Feeding a clock into an accumulator" )
{

    auto clock         = std::make_shared<Clock<double>>();
    auto accumulator   = std::make_shared<Accumulator>();
    accumulator->input = clock;
    CHECK_SIGNAL<double>( accumulator, { 0, 1, 3, 6, 10, 15 } );
}

TEST_CASE( "Using modulo to count to 10 repetitively" )
{
    auto clock   = std::make_shared<Clock<double>>();
    auto mod     = std::make_shared<Modulo>();
    mod->input   = clock;
    mod->maximum = 10;
    SignalReader<double> reader;
    reader = mod;

    REQUIRE( reader[1] == 1 );
    REQUIRE( reader[9] == 9 );
    REQUIRE( reader[15] == 5 );
}
