#include "../core.h"
#include "LazyRegex.h"

class NumberPatterns
{
public:
    static LazyRegex naturalNumber;
    static LazyRegex integer;

    static LazyRegex unsignedDecimal;
    static LazyRegex unsignedPointNumber;

    static LazyRegex number;

public:
    static Hopefully<float> parseNumber( const std::string& str )
    {
        if ( number.test( str ) )
            return stof( str );
        else
            return Disappointment;
    }
};
