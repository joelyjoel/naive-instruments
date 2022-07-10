#include "NumberWithUnit.h"

LazyRegex NumberWithUnit::pattern(NumberPatterns::number.capture() +
                                  LazyRegex::ignoreWhitespace +
                                  Units::pattern.capture().optional());
