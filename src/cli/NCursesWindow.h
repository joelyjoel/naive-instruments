#pragma once

#include <ncurses.h>

class NCursesWindow
{
private:
    WINDOW* win;

public:
    const int height, width;
    const int startY, startX;

public:
    NCursesWindow( int height, int width, int startY, int startX )
    : height( height )
    , width( width )
    , startY( startY )
    , startX( startX )
    {
        win = newwin( height, width, startY, startX );
    }

    void fill( const char* fillChar )
    {
        for ( int y = 0; y < height; ++y )
            for ( int x = 0; x < width; ++x )
                write( x, y, fillChar );
    }

    void write( int y, int x, const char* ch )
    {
        wmove( win, y, x );
        wprintw( win, ch );
    }

    chtype read( int y, int x )
    {
        // TODO: How are wide chars handled here?
        return mvwinch( win, y, x ) & A_CHARTEXT;
    }
    bool isEmpty( int y, int x )
    {
        return read( y, x ) == ' ';
    }

    void blank()
    {
        fill( " " );
    }

    int size()
    {
        return width * height;
    }
    void refresh()
    {
        wrefresh( win );
    }
};
