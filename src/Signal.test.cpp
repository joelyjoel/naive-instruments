#include "./Signal.h"
#include "../dependencies/catch.hpp"
#include <memory>

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

TEST_CASE( "Accessing a signal using a SignalReader" )
{
    SignalReader<int> clockReader;
    clockReader = std::make_shared<Clock<int>>();

    REQUIRE( clockReader[0] == 0 );
    REQUIRE( clockReader[1] == 1 );
    REQUIRE( clockReader[100] == 100 );
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

    auto                 clock       = std::make_shared<Clock<double>>();
    auto                 accumulator = std::make_shared<Accumulator>();
    SignalReader<double> reader;
    accumulator->input = clock;
    reader             = accumulator;
    REQUIRE( reader[1] == 1 );
    REQUIRE( reader[2] == 3 );
    REQUIRE( reader[3] == 6 );
    REQUIRE( reader[4] == 10 );
}
