#include "../core.h"

class Invert : public FrameStream<double>
{
public:
    FrameStreamConsumer<double> input{ this, "input" };

protected:
    void action() override
    {
        writeFrame( -input.readFrame() );
    }
};
