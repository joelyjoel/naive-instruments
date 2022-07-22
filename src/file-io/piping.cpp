#include "./piping.h"

bool stdinIsATerminal() { return isatty(fileno(stdin)); }

bool stdinIsAPipe() { return !stdinIsATerminal(); }

bool stdoutIsATerminal() { return isatty(fileno(stdout)); }

bool stdoutIsAPipe() { return !stdoutIsATerminal(); }
