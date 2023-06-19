#include "../lib.h"

class RulerCommand : public CommandLineApp
{
public:
    using CommandLineApp::CommandLineApp;

    void run()
    {
        setlocale( LC_ALL, "" );
        initscr();
        keypad( stdscr, TRUE );
        cbreak();

        refresh();

        NCursesWindow canvas( 2, 80, 3, 2 );
        Ruler         ruler( canvas );

        ruler.from = args.number( "from", 0 );
        ruler.to   = args.number( "to", 1 );

        ruler.draw();

        int c;
        while ( ( c = getch() ) != 'q' )
            continue;

        endwin();
    }
};
