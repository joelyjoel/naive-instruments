#pragma once

#include "./NCursesWindow.h"
#include <math.h>
#include <string>

using std::string;

class Ruler
{
public:
    float from, to;
    int   base = 10;

    NCursesWindow& canvas;

public:
    Ruler( NCursesWindow& canvas )
    : canvas( canvas )
    {
    }

private:
    void drawDivisions( float division )
    {
        for ( float time = ceil( from / division ) * division; time < to; time += division )
        {
            drawLabelIfThereIsRoom( time );
        }
    }

public:
    void draw()
    {
        drawAxis();
        drawDivisions( 1 );
        canvas.refresh();
    }

private:
    void drawLabelIfThereIsRoom( float time )
    {
        int    x     = xAtTime( time );
        string label = toLabelString( time );
        if ( thereIsSpace( x - 1, x + label.size() + 1 ) )
            drawLabel( x, label.c_str() );
    }

    void drawLabel( int x, const char* label )
    {
        canvas.write( 0, x, "\u2530" );
        canvas.write( 1, x, label );
    }

    /**
     * Draws a horizontal line with no markers yet.
     */
    void drawAxis()
    {
        for ( int x = 0; x < canvas.width; ++x )
            canvas.write( 0, x, "-" );
    }

    string toLabelString( float time )
    {
        return std::to_string( (int) time );
    }

    int xAtTime( float t )
    {
        return ( t - from ) / duration() * canvas.width;
    }
    double duration()
    {
        return to - from;
    }

    /**
     * Check that there is available space for a label between the two
     * x-coordinates.
     */
    bool thereIsSpace( int fromX, int toX )
    {
        // TODO: Read the ncurses window to see if there is available space
        for ( int x = fromX; x <= toX; ++x )
            if ( !canvas.isEmpty( 1, x ) )
                return false;
            else
                continue;
        // otherwise
        return true;
    }
};
