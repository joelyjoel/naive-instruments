#include "Signal.h"
#include "SignalShorthands.h"
#include "signal-processes.h"
#include <boost/algorithm/string.hpp>
#include <string>

inline std::string indentInPlace( std::string str, int numberOfSpaces = 2 )
{
    std::string spaces( 2, ' ' );
    boost::replace_all( str, "\n", "\n" + spaces );
    return spaces + str;
}


inline std::string signalProcessName( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
{
    using namespace NaiveInstruments;
    NaiveInstruments::UnknownOutputSignal& s = *signal;
    std::string                            t = typeid( s ).name();
    if ( t == typeid( NaiveInstruments::Constant<double> ).name() )
        return std::to_string( ( (NaiveInstruments::Constant<double>*) &s )->output );
    if ( t == typeid( NaiveInstruments::Multiply ).name() )
        return "*";
    if ( t == typeid( NaiveInstruments::LinearRamp ).name() )
        return "ramp";
    if ( t == typeid( NaiveInstruments::Sum<double> ).name() )
        return "+";
    if ( t == typeid( NaiveInstruments::USaw ).name() )
        return "usaw";
    if ( t == typeid( NaiveInstruments::Wavetable ).name() )
        return "wavetable";

    return typeid( s ).name();
}

inline std::string signalGraphStructureString( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
{
    std::string str = signalProcessName( signal );
    for ( auto input : signal->inputs )
    {
        str += "\n" + indentInPlace( signalGraphStructureString( input->abstract_ptr() ) );
    }
    return str;
}
