#include "Signal.h"
#include <memory>
#include <vector>
namespace NaiveInstruments
{
class SignalGraphExplorer
{
public:
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
};
} // namespace NaiveInstruments
