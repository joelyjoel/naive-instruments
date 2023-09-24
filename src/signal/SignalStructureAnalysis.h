#pragma once

#include "./Constructors.h"
#include "NodeGraph.h"
#include "Signal.h"
#include <memory>
#include <string>

namespace NaiveInstruments
{

/// A class for analysing the internal structure of signal.
class SignalStructureAnalysis
{
public:
    static std::string signalGraphStructureString( std::shared_ptr<UnknownOutputSignal> signal )
    {
        SignalStructureAnalysis instance;
        auto                    nodeGraph = instance.extractNodeGraph( signal );
        return nodeGraph->stringify();
    }

    std::shared_ptr<NodeGraph> extractNodeGraph( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
    {
        // Handle constants as a special case
        if ( typeid( *signal ).name() == typeid( Constant<double> ).name() )
        {
            auto constant = std::static_pointer_cast<Constant<double>>( signal );
            return std::make_shared<NodeGraph>( std::to_string( constant->output ) );
        }

        // Default handling
        auto node = std::make_shared<NodeGraph>( signalProcessName( signal ) );
        for ( auto input : signal->inputs )
        {
            auto subNode = extractNodeGraph( input->abstract_ptr() );
            node->addInput( subNode );
        }
        return node;
    }


    /// Get the name (type) of the head signal process
    std::string signalProcessName( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
    {
        auto recognised = standardSignalConstructor.recognise( signal );
        if ( recognised != "?" )
            return recognised;

        else
            return typeid( *signal ).name();
    }


    // TODO: Find unset inputs in a signal
    // TODO: list all processes in a signal
};
} // namespace NaiveInstruments
