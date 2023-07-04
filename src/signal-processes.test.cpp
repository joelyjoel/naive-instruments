#include "signal-processes.h"
#include "./test-framework/custom-assertions.h"
#include "core/MonoBuffer.h"

using namespace NaiveInstruments;

TEST_CASE( "Creating a vector signal" )
{
    auto buffer    = std::make_shared<std::vector<double>>( 5 );
    ( *buffer )[0] = 5;
    ( *buffer )[1] = 4;
    ( *buffer )[2] = 3;
    ( *buffer )[3] = 2;
    ( *buffer )[4] = 1;


    std::shared_ptr<Signal<double>> signal = std::make_shared<NaiveInstruments::VectorSignal>( buffer );

    CHECK_SIGNAL( signal, { 5, 4, 3, 2, 1 } );
}

TEST_CASE( "Creating a Sampler using a contrived MonoBuffer" )
{
    MonoBuffer buffer( 10 );
    buffer[0] = 5;
    buffer[1] = 4;
    buffer[2] = 3;
    buffer[3] = 2;
    buffer[4] = 1;

    std::shared_ptr<Signal<double>> sampler = std::make_shared<NaiveInstruments::Sampler>( &buffer );
    CHECK_SIGNAL( sampler, { 5, 4, 3, 2, 1 } );
}
