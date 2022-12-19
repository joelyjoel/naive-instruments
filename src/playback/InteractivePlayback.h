#pragma once

#include "../instruments/Pauser.h"
#include "../lib.h"
#include "BufferedPlayback.h"
#include <iostream>
#include <memory>
#include <ncurses.h>

class InteractivePlayback {
  BufferedPlayback bufferedPlayback;

  InteractivePlayback(Signal<double> &input) : bufferedPlayback(pauser) {
    attachPlaybackControls(input);
  }

  Pauser pauser;

  // TODO: Use smart pointers insteadh of references
  void attachPlaybackControls(Signal<double> &input) {
    // FIXME: Unsafe!
    std::shared_ptr<Signal<double>> inputptr(&input);
    pauser.input << inputptr;
  }

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
        if (c == 32)
          pauser.toggle();
        else if (c == 10)
          bufferedPlayback.resetSignal();
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
