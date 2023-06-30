#include "./Signal.h"
#include "../dependencies/catch.hpp"

TEST_CASE( "Overload Signal, instantiate and check that syncing advances the clock" )
{
    class PowersOfTwo : public Signal<double>
    {
    public:
        PowersOfTwo()
        {
            *output = 1;
        }
        void action() override
        {
            // No-op
            *output *= 2;
        }
    };

    PowersOfTwo a;
    a.sync( 9 );
    REQUIRE( a.t == 9 );
    REQUIRE( *a.output == 512 );


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
            output = 0;
        }
        void action() override
        {
            *output = t;
        }
    };

    SignalReader<int> clockReader;
    clockReader = std::make_shared<Clock>();

    /* REQUIRE( clockReader[0] == 0 ); */
}
