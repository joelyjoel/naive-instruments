#include "./Constructors.h"
#include "Signal.h"
#include "SignalShorthands.h"
#include "signal-processes.h"
#include <boost/algorithm/string.hpp>
#include <string>

namespace NaiveInstruments
{

class SignalGraph
{

    static std::string indentInPlace( std::string str )
    {
        std::string prefix = " └";
        std::string spaces = "  ";
        boost::replace_all( str, "\n", "\n" + spaces );
        return prefix + str;
    }


    static std::string signalProcessName( std::shared_ptr<UnknownOutputSignal> signal )
    {
        UnknownOutputSignal& s = *signal;
        std::string          t = typeid( s ).name();

        auto recognised = StandardSignalConstructor().recognise( signal );
        if ( recognised != "?" )
            return recognised;


        return typeid( s ).name();
    }

public:
    static std::string signalGraphStructureString( std::shared_ptr<UnknownOutputSignal> signal )
    {
        UnknownOutputSignal& s = *signal;
        std::string          t = typeid( s ).name();
        if ( t == typeid( Constant<double> ).name() )
            return std::to_string( ( (Constant<double>*) &s )->output );

        auto shortversion = inlineStructureString( signal );
        if ( shortversion.size() <= 80 )
            return shortversion;
        else
            return multilineStructureString( signal );
    }

    static std::string multilineStructureString( std::shared_ptr<UnknownOutputSignal> signal )
    {
        std::string str = signalProcessName( signal );
        str += ":";
        for ( auto input : signal->inputs )
        {
            str += "\n" + indentInPlace( signalGraphStructureString( input->abstract_ptr() ) );
        }
        return str;
    }

    static std::string inlineStructureString( std::shared_ptr<UnknownOutputSignal> signal )
    {
        std::string str = signalProcessName( signal );
        str += "(";
        for ( int i = 0; i < signal->inputs.size(); ++i )
        {
            if ( i != 0 )
                str += ", ";
            auto input = signal->inputs[i];
            str += signalGraphStructureString( input->abstract_ptr() );
        }
        str += ")";
        return str;
    }
};

} // namespace NaiveInstruments
