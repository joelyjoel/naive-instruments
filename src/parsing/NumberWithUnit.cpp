#include "NumberWithUnit.h"
#include "NumberPatterns.h"

LazyRegex NumberWithUnit::pattern(NumberPatterns::number.capture() +
                                  LazyRegex::ignoreWhitespace +
                                  Units::pattern.capture());
