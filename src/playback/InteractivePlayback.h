#pragma once

#include "../instruments/Pacer.h"
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
  Pacer pacer;

  // TODO: Use smart pointers insteadh of references
  void attachPlaybackControls(Signal<double> &input) {
    // FIXME: Unsafe!
    std::shared_ptr<Signal<double>> inputptr(&input);
    pacer.rate << 1;
    pacer.input << inputptr;
    // FIXME: Unsafe again!
    pauser.input << std::shared_ptr<Pacer>(&pacer);
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
        else if (c == '=')
          pacer.rate << (pacer.rate.currentConstant() * pow(2.0, (1 / 12.0)));
        else if (c == '-')
          pacer.rate << (pacer.rate.currentConstant() / pow(2.0, (1 / 12.0)));
        else if (c == '+')
          pacer.rate << (pacer.rate.currentConstant() * pow(2.0, (.05 / 12.0)));
        else if (c == '_')
          pacer.rate << (pacer.rate.currentConstant() / pow(2.0, (.05 / 12.0)));

        render();
      }
    });
  }

  void render() {
    // TODO: Separate class for rendering state?
    // TODO: Eventually use a query string or something for UI components
    clear();
    string str ;
    // TODO: Should be a sub function
    str += "Playback rate = " + std::to_string(pacer.rate.currentConstant()) + "\n";
    // TODO: Should be another sub function
    if (pauser.is_paused())
      str += "Paused\n";
    else 
      str += "Playing\n";
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
