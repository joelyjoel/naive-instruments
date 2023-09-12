#include "Signal.h"
#include "SignalShorthands.h"
#include <boost/algorithm/string.hpp>
#include <string>

inline std::string indentInPlace( std::string str, int numberOfSpaces = 2 )
{
    std::string spaces( 2, ' ' );
    boost::replace_all( str, "\n", "\n" + spaces );
    return spaces + str;
}

inline std::string signalGraphStructureString( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
{
    std::string str = typeid( *signal ).name();
    for ( auto input : signal->inputs )
    {
        str += "\n" + indentInPlace( signalGraphStructureString( input->abstract_ptr() ) );
    }
    return str;
}
