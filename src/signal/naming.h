#include <string>

class NamedThing
{
public:
    virtual const std::string name() = 0;
};

template <size_t N>
struct StringLiteral
{
    constexpr StringLiteral( const char ( &str )[N] )
    {
        std::copy_n( str, N, value );
    }

    char value[N];
};

template <StringLiteral NAME>
class WithName : public NamedThing
{
public:
    const std::string name() override
    {
        return NAME.value;
    }
};
