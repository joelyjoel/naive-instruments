#include "LazyRegex.h"

LazyRegex operator+(const string &a, const LazyRegex &b) { return a + b.src(); }

LazyRegex LazyRegex::ignoreWhitespace("\\s*");
