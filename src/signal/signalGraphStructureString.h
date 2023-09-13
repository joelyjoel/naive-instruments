#include "./Constructors.h"
#include "Signal.h"
#include "SignalShorthands.h"
#include "signal-processes.h"
#include <boost/algorithm/string.hpp>
#include <string>


class SignalGraph
{

    static std::string indentInPlace( std::string str )
    {
        std::string prefix = " ┗━◀ ";
        std::string spaces = "     ";
        boost::replace_all( str, "\n", "\n" + spaces );
        return prefix + str;
    }


    static std::string signalProcessName( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
    {
        using namespace NaiveInstruments;
        NaiveInstruments::UnknownOutputSignal& s = *signal;
        std::string                            t = typeid( s ).name();
        if ( t == typeid( NaiveInstruments::Constant<double> ).name() )
            return std::to_string( ( (NaiveInstruments::Constant<double>*) &s )->output );

        auto recognised = StandardSignalConstructor().recognise( signal );
        if ( recognised != "?" )
            return recognised;


        return typeid( s ).name();
    }

public:
    static std::string signalGraphStructureString( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
    {
        std::string str = signalProcessName( signal );
        for ( auto input : signal->inputs )
        {
            str += "\n" + indentInPlace( signalGraphStructureString( input->abstract_ptr() ) );
        }
        return str;
    }
};
