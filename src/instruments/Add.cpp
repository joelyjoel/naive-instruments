#include "Add.h"

// TODO: Refactor to use the + operator overloads
void operator+=( FrameStreamConsumer<double>& signalInput, std::shared_ptr<FrameStream<double>> additionalSignal )
{
    std::shared_ptr<Add> add = std::make_shared<Add>();
    add->a << signalInput.typedConnection();
    add->b << additionalSignal;
    signalInput << add;
}

std::shared_ptr<FrameStream<double>> operator+( std::shared_ptr<FrameStream<double>> a,
                                                std::shared_ptr<FrameStream<double>> b )
{
    std::shared_ptr<Add> add = std::make_shared<Add>();
    add->a << a;
    add->b << b;
    return add;
}
