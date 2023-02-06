#pragma once

#include "../instruments/CDJ.h"
#include "../lib.h"
#include "BufferedPlayback.h"
#include <iostream>
#include <memory>
#include <ncurses.h>

const float frameRate = 31;

class InteractivePlayback {
  BufferedPlayback bufferedPlayback;

  CDJ cdj;

  InteractivePlayback(Signal<double> &input) : bufferedPlayback(cdj) {
    attachPlaybackControls(input);
  }

  // TODO: Use smart pointers insteadh of references
  void attachPlaybackControls(Signal<double> &input) {
    // FIXME: Unsafe!
    std::shared_ptr<Signal<double>> inputptr(&input);
    cdj.input << inputptr;
  }

  void start(bool async = false) {
    std::cerr << "Starting interactive playback";
    startCursesThread();
    bufferedPlayback.start(async);
  }

  std::thread *renderThread;

  std::thread *cursesThread;
  void startCursesThread() {
    setlocale(LC_ALL, "");
    initscr();
    mouseinterval(0);
    mousemask(BUTTON1_CLICKED | BUTTON4_PRESSED | BUTTON2_PRESSED, NULL);
    cursesThread = new std::thread([this]() {
      while (true) {
        int c = getch();
        if (c == 32)
          cdj.togglePause();
        else if (c == 10)
          cdj.restart();
        else if (c == '=')
          cdj.semitoneFaster();
        else if (c == '-')
          cdj.semitoneSlower();
        else if (c == '+')
          cdj.semitoneFaster(.05);
        else if (c == '_')
          cdj.semitoneSlower(.05);
        else if (c == '\'')
          cdj.punchLoop();
        else if (c == 'h')
          cdj.skipForward(-.250);
        else if (c == 'l')
          cdj.skipForward(.250);
      }
    });
    renderThread = new std::thread([this]() {
      while (true) {
        render();
        refresh();
        napms(1000.0 / frameRate);
      }
    });
  }

  void render() {
    // TODO: Separate class for rendering state?
    // TODO: Eventually use a query string or something for UI components
    clear();
    string str;
    // TODO: Should be a sub function
    // TODO: Should be another sub function
    if (cdj.isPaused())
      str += "\uf04c";
    else
      str += "\uf04b";

    str += " " + cdj.describeTimeElapsed() + "\t";

    str += "\uf04e x" + std::to_string(cdj.playbackRate()) + "\t";

    str += "Detune " + cdj.describeDetune() + "\t";

    str += cdj.describeLoopState() + "\t\t";

    addstr(str.c_str());
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
