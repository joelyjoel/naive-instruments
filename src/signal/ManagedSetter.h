#include <string>

namespace NaiveInstruments
{
class UnknownOutputSignal;

class AbstractManagedAccessor
{
public:
    bool has_been_set_manually = false;
    bool has_been_set          = false;

    virtual std::shared_ptr<UnknownOutputSignal> get_signal()
    {
        return nullptr;
    }
};

template <typename T>
class ManagedAccessor : public AbstractManagedAccessor
{
protected:
    T& resource;

public:
    ManagedAccessor( T& resource )
    : resource( resource )
    {
    }


    template <typename U>
    void assign_manually( U& value )
    {
        has_been_set          = true;
        has_been_set_manually = true;
        resource              = value;
    }
};
} // namespace NaiveInstruments
