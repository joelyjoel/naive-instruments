#include "../lib.h"
#include <iostream>
#include <string>

class GraphApp : public CommandLineApp {
  using CommandLineApp::CommandLineApp;

public:
  void run() override {
    if (args.boolean("i"))
      interactiveMode();
    else
      stdoutMode();
  }

  void interactiveMode() {
    setlocale(LC_ALL, "");
    initscr();
    mouseinterval(0);
    mousemask(BUTTON1_CLICKED | BUTTON4_PRESSED | BUTTON2_PRESSED, NULL);

    double from = 0;
    double to = 0.1;

    WavReader file(args[0]);
    while (true) {
      int c = getch();

      double increment = (to - from) / 10;

      switch (c) {
      case KEY_MOUSE:
        throw 69;
        break;
      case 'h':
        from -= increment;
        to -= increment;
        break;
      case 'l':
        from += increment;
        to += increment;
        break;
      case '+':
        to -= increment;
        from += increment;
        break;
      case '-':
        to += increment;
        from -= increment;
        break;
      case '=':
        from = 0;
        to = file.duration();
      }

      clear();
      move(0, 0);

      RectangleBuffer<std::string> canvas(120, 30);
      RmsAsciGrapher::fromFile(canvas, args[0], from, to);

      move(3, 0);
      // printw(cppstr.c_str());
      for (int y = 0; y < canvas.height; ++y)
        for (int x = 0; x < canvas.width; ++x) {
          move(y, x);
          printw(canvas.cell(x, y).c_str());
        }

      refresh();

      // printw("%ls", output.str().c_str());
    }
    endwin();
  }

  void stdoutMode() {
    for (int i = 0; i < args.numberOfPositionalArgs(); ++i) {
      auto inputFile = args[i];

      RmsAsciGrapher grapher;

      int width = args.integer("width", 80);
      int height = args.integer("height", 9);

      RectangleBuffer<std::string> canvas(width, height);

      grapher.fromFile(canvas, inputFile);

      canvas.stream(std::cout);
    }
  }
};
