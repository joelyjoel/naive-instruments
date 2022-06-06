#include "../lib.h"

int main(int argv, char **argc) {
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  cbreak();

  refresh();

  NCursesWindow canvas(2, 80, 3, 2);
  Ruler ruler(canvas);

  ruler.from = 0;
  ruler.to = 10;

  ruler.draw();

  // WINDOW *win = newwin(30, 30, 10, 10);

  //// wmove(win, 0, 0);
  // wprintw(win, "osuhtkoeuhxd");
  // wrefresh(win);

  int c;
  while ((c = getch()) != 'q')
    continue;

  endwin();
}
