#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h>    // for STDOUT_FILENO

class WindowDimensions {
public:
  static int height() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    return size.ws_row;
  }
  static int width() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    return size.ws_col;
  }
};
