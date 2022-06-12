#include "../lib.h"

// TODO: Use full screen width

int main(int argc, char **argv) {
  CommandLineArguments args(argc, argv);
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  cbreak();

  refresh();

  NCursesWindow canvas(2, 80, 3, 2);
  Ruler ruler(canvas);

  ruler.from = args.number("from", 0);
  ruler.to = args.number("to", 1);

  ruler.draw();

  int c;
  while ((c = getch()) != 'q')
    continue;

  endwin();
}
