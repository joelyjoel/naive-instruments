#include "./Signal.h"
#include "../dependencies/catch.hpp"

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
    /// Comprised signal that writes the frame position to the output field
    class Clock : public Signal<int>
    {
    public:
        Clock()
        {
            output = t;
        }
        void action() override
        {
            output = t;
        }
    };

    SignalReader<int> clockReader;
    clockReader = std::make_shared<Clock>();

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
