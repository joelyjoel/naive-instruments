#pragma once

#include "../core.h"
#include "NumberPatterns.h"
#include "Units.h"
#include <regex>

class NumberWithUnit
{
public:
    float       number;
    Units::Unit unit;

    NumberWithUnit( float n, Units::Unit unit )
    : number( n )
    , unit( unit )
    {
    }
    NumberWithUnit()
    : number( 0 )
    , unit( Units::noUnit )
    {
    }

    static LazyRegex pattern;

    static Hopefully<NumberWithUnit> parse( const std::string& str )
    {
        std::smatch result;
        if ( std::regex_match( str, result, *pattern ) )
        {
            Hopefully<float>       n = NumberPatterns::parseNumber( result[1] );
            Hopefully<Units::Unit> u = Units::parse( result[2] );
            if ( n.success() && u.success() )
                return NumberWithUnit( *n, *u );
            else
                return Disappointment;
        }
        else
            return Disappointment;
    }

    Hopefully<float> interval() const
    {
        switch ( unit )
        {
            case Units::noUnit:
            case Units::seconds:
                return number;
            case Units::bpm:
                return 1.0 / ( number / 60.0 );
            case Units::Hz:
                return 1.0 / number;
            case Units::milliseconds:
                return number * .001;
            case Units::minutes:
                return number * 60;
            case Units::hours:
                return number * 60 * 60;
            case Units::samples:
                return number / float( sampleRate );
            default:
                throw Disappointment;
        }
    }

    /**
     * Parse a number with unit as an interval in seconds.
     */
    static Hopefully<float> parseInterval( const std::string& str )
    {
        auto nu = parse( str );
        if ( nu.success() )
        {
            return nu->interval();
        }
        else
            return Disappointment;
    }
};
