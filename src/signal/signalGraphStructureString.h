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
        SignalGraph instance;
        return instance.graph( signal );
    }


private:
    SignalGraph()
    {
        seenBefore.clear();
    }

    std::vector<std::shared_ptr<UnknownOutputSignal>> seenBefore;
    bool                                              checkBreadcrumbs( std::shared_ptr<UnknownOutputSignal> signal )
    {
        for ( int i = 0; i < seenBefore.size(); ++i )
        {
            if ( seenBefore[i] == signal )
                return true;
        }
        seenBefore.push_back( signal );
        // otherwise
        return false;
    }


    typedef struct NodeT
    {
        std::string                         head;
        std::vector<std::shared_ptr<NodeT>> inputs;
    } Node;


    NodeT nodeGraph(){

    };


    std::string graph( std::shared_ptr<UnknownOutputSignal> signal )
    {
        if ( checkBreadcrumbs( signal ) )
            return "feedback";

        UnknownOutputSignal& s = *signal;
        std::string          t = typeid( s ).name();
        if ( t == typeid( Constant<double> ).name() )
            return std::to_string( ( (Constant<double>*) &s )->output );


        // FIXME: THE BUG IS BECAUSE we are running it twice, so every thing appears in breadcrumbs twice
        // A solution could be to use an intermediate structure, for signal graph hierarchy


        auto shortversion = inlineStructureString( signal );
        if ( shortversion.size() <= 80 && shortversion.find( "\n" ) == std::string::npos )
            return shortversion;
        else
            return multilineStructureString( signal );
    }

    std::string multilineStructureString( std::shared_ptr<UnknownOutputSignal> signal )
    {
        std::string str = signalProcessName( signal );
        str += ":";
        for ( auto input : signal->inputs )
        {
            str += "\n" + indentInPlace( graph( input->abstract_ptr() ) );
        }
        return str;
    }

    std::string inlineStructureString( std::shared_ptr<UnknownOutputSignal> signal )
    {
        std::string str = signalProcessName( signal ) + "(";
        for ( int i = 0; i < signal->inputs.size(); ++i )
        {
            if ( i != 0 )
                str += ", ";
            auto input = signal->inputs[i];
            str += graph( input->abstract_ptr() );
        }
        str += ")";
        return str;
    }
};

} // namespace NaiveInstruments
