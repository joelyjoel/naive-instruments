
#include "./SignalString.h"

void operator<<( FrameStreamConsumer<double>& input, const std::string& str )
{
    input << SignalString::parse( str );
}
