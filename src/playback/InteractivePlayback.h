#pragma once

#include "../lib.h"
#include "BufferedPlayback.h"
#include <iostream>
#include <ncurses.h>

class InteractivePlayback {
  BufferedPlayback bufferedPlayback;

  InteractivePlayback(Signal<double> &input) : bufferedPlayback(input) {}

  void start(bool async = false) {
    std::cerr << "Starting interactive playback";
    startCursesThread();
    bufferedPlayback.start(async);
  }

  std::thread *cursesThread;
  void startCursesThread() {
    setlocale(LC_ALL, "");
    initscr();
    mouseinterval(0);
    mousemask(BUTTON1_CLICKED | BUTTON4_PRESSED | BUTTON2_PRESSED, NULL);
    cursesThread = new std::thread([this]() {
      while (true) {
        int c = getch();
        std::cerr << "Keypress! " << c << "\n";
      }
    });
  }

public:
  static void play(Signal<double> &signal) {
    InteractivePlayback playback(signal);
    playback.start(false);
  }

  static void play(MonoBuffer &audio) {
    // FIXME: Memory leak!
    Sampler *sampler = new Sampler(audio);
    play(*sampler);
  }
};
