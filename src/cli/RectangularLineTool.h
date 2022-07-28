#pragma once

#include "./RectangleBuffer.h"
#include <iostream>
#include <string>

class RectangularLineTool {
  int x0;
  int y0;

public:
  void moveTo(int x, int y) {
    x0 = x;
    y0 = y;
  }

public:
  void lineTo(int x, int y) {
    while (x > x0)
      right();
    while (x < x0)
      left();
    while (y < y0)
      down();
    while (y > y0)
      up();
  }

private:
  RectangleBuffer<std::string> &canvas;

public:
  RectangularLineTool(RectangleBuffer<std::string> &canvas) : canvas(canvas) {
    moveTo(0, 0);
  }

private:
  void plot(std::string c) {
    if (x0 > 0 && x0 < canvas.width && y0 > 0 && y0 < canvas.height)
      canvas(x0, y0) = c;
  }

private:
  typedef enum { Up, Down, Left, Right } Direction;

  Direction previousMovement;
  void up() {
    if (previousMovement == Up || previousMovement == Down)
      plot("\u2502");
    else if (previousMovement == Right)
      plot("\u256e");
    else if (previousMovement == Left)
      plot("\u256d");
    ++y0;
    previousMovement = Up;
  }

  void down() {
    if (previousMovement == Up || previousMovement == Down)
      plot("\u2502");
    else if (previousMovement == Right)
      plot("\u256f");
    else if (previousMovement == Left)
      plot("\u2570");
    --y0;
    previousMovement = Down;
  };

  void left() {
    if (previousMovement == Left || previousMovement == Right)
      plot("\u2500");
    else if (previousMovement == Up)
      plot("\u256f");
    else if (previousMovement == Down)
      plot("\u256e");
    --x0;
    previousMovement = Left;
  }

  void right() {
    if (previousMovement == Left || previousMovement == Right)
      plot("\u2500");
    else if (previousMovement == Up)
      plot("\u2570");
    else if (previousMovement == Down)
      plot("\u256d");
    ++x0;
    previousMovement = Right;
  };
};
