#include "Add.h"

// TODO: Refactor to use the + operator overloads
void operator+=( FrameStreamConsumer<double>& signalInput, shared_ptr<FrameStream<double>> additionalSignal )
{
    shared_ptr<Add> add = make_shared<Add>();
    add->a << signalInput.typedConnection();
    add->b << additionalSignal;
    signalInput << add;
}

shared_ptr<FrameStream<double>> operator+( shared_ptr<FrameStream<double>> a, shared_ptr<FrameStream<double>> b )
{
    shared_ptr<Add> add = make_shared<Add>();
    add->a << a;
    add->b << b;
    return add;
}
