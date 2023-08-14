#include "./RuntimeSignalConstructor.h"
#include "../test-framework/custom-assertions.h"


TEST_CASE( "Can use StandardSignalShorthands to create a usaw" )
{
    StandardSignalShorthands constructor;
    auto                     signal = constructor.construct( "usaw" );

    CHECK( typeid( *signal ) == typeid( NaiveInstruments::USaw ) );
    CHECK( typeid( *constructor( "usaw" ) ) == typeid( NaiveInstruments::USaw ) );
    CHECK( typeid( *constructor( "+" ) ) == typeid( NaiveInstruments::Sum<double> ) );
    CHECK( typeid( *constructor( "-" ) ) == typeid( NaiveInstruments::Subtract<double> ) );
}
