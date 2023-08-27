#include "Signal.h"
#include <algorithm>
#include <memory>
#include <vector>
namespace NaiveInstruments
{
class SignalGraphExplorer
{
public:
    /**
     * List the signals which are a direct input to the given signal.
     */
    static std::vector<std::shared_ptr<UnknownOutputSignal>> directSignalInputs(
        std::shared_ptr<UnknownOutputSignal> signal )
    {
        std::vector<std::shared_ptr<UnknownOutputSignal>> list;
        for ( auto input : signal->inputs )
        {
            auto sig = input->get_signal();
            if ( sig )
                list.push_back( sig );
        }
        return list;
    }

    /**
     * List all the signals which are direct or indirect inputs to the given signal by exploring the graph recursively.
     */
    static std::vector<std::shared_ptr<UnknownOutputSignal>> recursiveSignalInputs(
        std::shared_ptr<UnknownOutputSignal> startingPoint,
        /**
         * Should the starting point be included in the results?
         */
        bool inclusive = false )
    {
        std::vector<std::shared_ptr<UnknownOutputSignal>> list;
        list.push_back( startingPoint );
        for ( int i = 0; i < list.size(); ++i )
        {
            auto current      = list[i];
            auto directInputs = directSignalInputs( current );
            for ( auto directInput : directInputs )
                if ( !std::count( list.begin(), list.end(), directInput ) )
                    list.push_back( directInput );
        }

        if ( !inclusive )
            list.erase( list.begin() );

        return list;
    }

    static std::vector<AbstractManagedAccessor*> listUnassignedAccessors( std::shared_ptr<UnknownOutputSignal> signal )
    {
        std::vector<AbstractManagedAccessor*> list;
        for ( auto accessor : signal->inputs )
            if ( !accessor->has_been_set_manually )
                list.push_back( accessor );
        return list;
    }

    /**
     * List all the unassigned managed accessors in a signal graph
     */
    static std::vector<AbstractManagedAccessor*> recursivelyListUnassignedAccessors(
        std::shared_ptr<UnknownOutputSignal> startingPoint )
    {
        static std::vector<AbstractManagedAccessor*> list;
        auto                                         allProcesses = recursiveSignalInputs( startingPoint, true );
        for ( auto process : allProcesses )
        {
            for ( auto accessor : listUnassignedAccessors( process ) )
            {
                list.push_back( accessor );
            }
        }
        return list;
    }
};
} // namespace NaiveInstruments
