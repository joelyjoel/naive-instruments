#pragma once

#include <iostream>
#include <ostream>

using std::ostream;

template <typename Cell = char> class RectangleBuffer {
private:
  typedef unsigned short Index;
  Cell *cells;

public:
  const Index width;
  const Index height;

public:
  RectangleBuffer(Index width, Index height) : width(width), height(height) {
    cells = new Cell[width * height];
  }
  RectangleBuffer(const RectangleBuffer<Cell> &that) { throw 2929; }

  // RectangleBuffer(Cell *cellsPtr, Index width, Index height)
  //: width(width), height(height) {
  // cells = cellsPtr;
  //}
  // TODO: Add move semantics
  ~RectangleBuffer() { delete[] cells; }

  const Index size() { return width * height; }
  Cell &cell(Index x, Index y) { return cell(y * width + x); }
  Cell &cell(Index i) {
    assert(i < size());
    return cells[i];
  }
  Cell &operator()(Index x, Index y) { return cell(x, y); }

  void fill(Cell value) {
    for (int i = 0; i < size(); ++i)
      cell(i) = value;
  };

  void stream(ostream &out) {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x)
        out << cell(x, y);
      out << "\n";
    }
  }

  // TODO: RectangleBuffer slice()
  // TODO: RectangleBuffer flip()
};

template <typename Cell>
ostream &operator<<(ostream &out, RectangleBuffer<Cell> &buffer) {
  buffer.stream(out);
  return out;
};
