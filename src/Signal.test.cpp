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
