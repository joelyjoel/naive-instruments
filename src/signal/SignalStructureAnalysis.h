#pragma once

#include "./Constructors.h"
#include "NodeGraph.h"
#include "Signal.h"
#include <memory>
#include <string>
#include <vector>

namespace NaiveInstruments
{

/// A class for analysing the internal structure of signal.
class SignalStructureAnalysis
{
public:
    static std::string signalGraphStructureString( std::shared_ptr<UnknownOutputSignal> signal )
    {
        NodeGraphExtracter instance( signal );
        auto               nodeGraph = instance.extractNodeGraph();
        return nodeGraph->stringify();
    }


    /// Get the name (type) of the head signal process
    static std::string signalProcessName( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
    {
        auto recognised = standardSignalConstructor.recognise( signal );
        if ( recognised != "?" )
            return recognised;

        else
            return typeid( *signal ).name();
    }


    // TODO: Find unset inputs in a signal
    // TODO: list all processes in a signal

    /**
     * A class for taking a signal and mapping out its internal structure using a node graph.
     */
    class NodeGraphExtracter
    {
        /**
         * These breadcrumb pointers are used to circuit break when analyising signals that contain feedback
         */
        std::vector<std::shared_ptr<UnknownOutputSignal>> breadcrumbs;
        bool checkInWithBreadcrumbs( std::shared_ptr<UnknownOutputSignal> signal )
        {
            if ( find( breadcrumbs.begin(), breadcrumbs.end(), signal ) != breadcrumbs.end() )
                return true;
            else
                breadcrumbs.push_back( signal );
        }
        // TODO: there could be a separate class `Breadcrumbs<UnknownOutputSignal>` to make this behaviour a bit more
        // standard

    public:
        std::shared_ptr<UnknownOutputSignal> startingPoint;
        NodeGraphExtracter( std::shared_ptr<UnknownOutputSignal> startingPoint )
        : startingPoint( startingPoint )
        {
        }

        std::shared_ptr<NodeGraph> extractNodeGraph()
        {
            return extractNodeGraph( startingPoint );
        }

        std::shared_ptr<NodeGraph> extractNodeGraph( std::shared_ptr<UnknownOutputSignal> signal )
        {

            // Check for for feedback
            if ( checkInWithBreadcrumbs( signal ) )
                return std::make_shared<NodeGraph>( "FEEDBACK" );

            // Handle constants as a special case
            if ( isConstant( signal ) )
                return std::make_shared<NodeGraph>( stringifyConstant( signal ) );

            // Default handling
            auto node = std::make_shared<NodeGraph>( signalProcessName( signal ) );
            for ( auto input : signal->inputs )
            {
                auto subNode = extractNodeGraph( input->abstract_ptr() );
                node->addInput( subNode );
            }
            return node;
        }
    };

private:
    /// Check if the signal is a mono-constant (`Constant<double>`)
    static bool isConstant( std::shared_ptr<UnknownOutputSignal> signal )
    {
        return typeid( *signal ).name() == typeid( Constant<double> ).name();
    }

    /// Turn a constant signal into a number string
    static std::string stringifyConstant( std::shared_ptr<UnknownOutputSignal> signal )
    {
        auto constant = std::static_pointer_cast<Constant<double>>( signal );
        return std::to_string( constant->output );
    }
};


} // namespace NaiveInstruments
