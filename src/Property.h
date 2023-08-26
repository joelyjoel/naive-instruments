class AbstractProperty
{
};

template <typename T>
class Property : public AbstractProperty
{
    T* pointer;

    template <typename U>
    void operator()( U& value )
    {
        *pointer = value;
    }
};
