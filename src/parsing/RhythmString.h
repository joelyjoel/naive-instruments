#include <iostream>
#include <string>
#include <vector>

/**
 * A class for parsing strings that represent RhythmString
 */
class RhythmString
{
public:
    static std::vector<float> parse( const std::string& str )
    { // TODO: Use a dictionary for named rhythms instead?
        if ( str == "son" || str == "son32" )
            return parse( "1001001000101000" );
        else if ( str == "rhumba" || str == "rhumba32" )
            return parse( "1001000100101000" );
        else if ( str == "son23" )
            return parse( "0010100010010010" );
        else if ( str == "rhumba23" )
            return parse( "0010100010010001" );
        else if ( str == "+" )
            return parse( "x8 0+" );
        else if ( str == "e" )
            return parse( "x16 0100" );
        else if ( str == "u" )
            return parse( "x16 0001" );

        std::vector<float> durations = { 0 };
        for ( int i = 0; i < str.size(); ++i )
        {
            char c = str[i];

            if ( c == '0' || c == '.' )
                durations[durations.size() - 1] += .5;
            else if ( c == '1' || c == '!' )
                durations.push_back( .5 );
            else
            {
                std::cerr << "Unexpected char '" << c << "' while parsing rhythm\n";
                throw 1;
            }
        }
        return durations;
    }
};
