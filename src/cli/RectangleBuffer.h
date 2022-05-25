#pragma once

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
  RectangleBuffer(Index width, Index Height) : width(width), height(height) {
    cells = new Cell[width * height];
  }
  RectangleBuffer(Cell *cellsPtr, Index width, Index height)
      : width(width), height(height) {
    cells = cellsPtr;
  }
  // TODO: Add move semantics
  ~RectangleBuffer() { delete cells; }

  const Index size() { return width * height; }
  Cell &cell(unsigned short x, unsigned short y) { return cell(y * width + x); }
  Cell &cell(Index i) {
    assert(i < size());
    return cells[i];
  }

  ostream &stream(ostream &out) {
    for (int y = 0; y < height; ++y)
      for (int x = 0; x < width; ++x)
        out << cell(x, y);
  }

  // TODO: RectangleBuffer slice()
  // TODO: RectangleBuffer flip()
};

template <typename Cell>
ostream &operator<<(ostream &out, RectangleBuffer<Cell> &buffer) {
  buffer.stream(out);
};
