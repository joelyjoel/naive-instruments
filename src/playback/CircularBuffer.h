
#include <iostream>
template <typename T> class CircularBuffer {
private:
  const int bufferSize;
  T *const buffer;

  int readHead = 0;
  int writeHead = 1;

public:
  CircularBuffer(int size) : bufferSize(size), buffer(new T[size]) {}

  void push(T y) {
    buffer[writeHead] = y;
    writeHead = (writeHead + 1) % bufferSize;
  }

  T shift() {
    T y = buffer[readHead];
    buffer[readHead] = 0;
    readHead = (readHead + 1) % bufferSize;
    return y;
  }

  bool hasFreeSpace() { return readHead != writeHead; }
  int size() { return bufferSize; }
};
