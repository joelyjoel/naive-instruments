
template <typename T> class CircularBuffer {
private:
  const int bufferSize;
  T *const buffer;

  int readHead = 0;
  int writeHead = 0;

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
};
