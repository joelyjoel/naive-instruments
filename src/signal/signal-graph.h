#include "./SignalShorthands.h"

inline std::string bracket_signal_graph( std::shared_ptr<NaiveInstruments::UnknownOutputSignal> signal )
{
    std::string inputs = "";
    if ( signal->inputs.size() == 0 )
        return signal->name();
    else
    {
        for ( int i = 0; i < signal->inputs.size(); ++i )
        {
            inputs += bracket_signal_graph( signal->inputs[i]->abstract_ptr() );
            if ( i != signal->inputs.size() - 1 )
                inputs += ", ";
        }

        return signal->name() + "(" + inputs + ")";
    }
}
