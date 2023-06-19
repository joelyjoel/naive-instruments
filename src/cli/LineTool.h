#pragma once

#include "./RectangleBuffer.h"

class LineTool
{
    RectangleBuffer<char>& canvas;

public:
    LineTool( RectangleBuffer<char>& canvas )
    : canvas( canvas )
    {
    }

    float x0;
    float y0;
    void  moveTo( float x, float y )
    {
        x0 = x;
        y0 = y;
    }

    int  segmentIndex = 0;
    void lineTo( float x1, float y1 )
    {
        plotLine( x0, y0, x1, y1 );
        moveTo( x1, y1 );
    }

    void plotLine( float x0, float y0, float x1, float y1 )
    {
        if ( abs( y1 - y0 ) < abs( x1 - x0 ) )
        {
            if ( x0 > x1 )
                plotLineLow( x1, y1, x0, y0 );
            else
                plotLineLow( x0, y0, x1, y1 );
        }
        else
        {
            if ( y0 > y1 )
                plotLineHigh( x1, y1, x0, y0 );
            else
                plotLineHigh( x0, y0, x1, y1 );
        }
    }

    void plotLineLow( float x0, float y0, float x1, float y1 )
    {
        int  dx     = x1 - x0;
        int  dy     = y1 - y0;
        int  yi     = 1;
        char symbol = '*';
        if ( dy < 0 )
        {
            yi = -1;
            dy = -dy;
        }
        int D = ( 2 * dy ) - dx;
        int y = y0;

        for ( int x = x0; x < x1; ++x )
        {
            canvas( x, y ) = symbol;
            if ( D > 0 )
            {
                y = y + yi;
                D = D + ( 2 * ( dy - dx ) );
            }
            else
                D = D + 2 * dy;
        }
    }

    void plotLineHigh( int x0, int y0, int x1, int y1 )
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int xi = 1;
        if ( dx < 0 )
        {
            xi = -1;
            dx = -dx;
        }
        int D = ( 2 * dx ) - dy;
        int x = x0;

        for ( int y = y0; y < y1; ++y )
        {
            canvas( x, y ) = '*';
            if ( D > 0 )
            {
                x = x + xi;
                D = D + ( 2 * ( dx - dy ) );
            }
            else
                D = D + 2 * dx;
        }
    }
};
