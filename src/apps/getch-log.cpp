#include <iostream>
#include <ncurses.h>
#include <stdio.h>

int main() {
  initscr();
  int c = getch();
  std::cout << c << "\n";
  endwin();
}
