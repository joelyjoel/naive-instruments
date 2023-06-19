#include "RectangleBuffer.h"
#include <string>
class TextTool
{
private:
    RectangleBuffer<std::string>& canvas;

    int x = 0;
    int y = 0;

    void plot( char c )
    {
        if ( x < canvas.width && x >= 0 && y >= 0 && y < canvas.height )
            canvas( x, y ) = c;
    }

public:
    TextTool( RectangleBuffer<std::string>& canvas )
    : canvas( canvas )
    {
    }

    void moveTo( int x, int y )
    {
        x = x;
        y = y;
    }

    void write( const std::string& str )
    {
        for ( int i = 0; i < str.size(); ++i )
        {
            ++x;
            plot( str[i] );
        }
    }
};
