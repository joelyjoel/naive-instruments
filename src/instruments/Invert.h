#include "../core.h"

class Invert : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> input{ this, "input" };

protected:
    void action() override
    {
        output[0] = -input.readFrame();
    }
};
