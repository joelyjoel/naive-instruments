#include "Multiply.h"

// FIXME: This causes a memory leak!
void operator*=( FrameStreamConsumer<double>& signalInput, std::shared_ptr<FrameStream<double>> scale )
{
    std::shared_ptr<Multiply> multiply = std::make_shared<Multiply>();
    multiply->a << signalInput.typedConnection();
    multiply->b << scale;
    signalInput << multiply;
}

std::shared_ptr<FrameStream<double>> operator*( std::shared_ptr<FrameStream<double>> a,
                                                std::shared_ptr<FrameStream<double>> b )
{
    std::shared_ptr<Multiply> m = std::make_shared<Multiply>();
    m->a << a;
    m->b << b;
    return m;
}
