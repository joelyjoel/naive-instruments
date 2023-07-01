#include "./SignalShorthands.h"
#include <memory>

using namespace SignalShorthands;

mono SignalShorthands::t()
{
    return std::make_shared<Clock<double>>();
}

mono SignalShorthands::add( mono a, mono b )
{
    auto adder    = std::make_shared<Sum<double>>();
    adder->input1 = a;
    adder->input2 = b;
    return adder;
}
