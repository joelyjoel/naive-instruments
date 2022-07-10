#include "NumberWithUnit.h"
#include "NumberPatterns.h"

LazyRegex NumberWithUnit::pattern(NumberPatterns::number +
                                  Units::pattern.bracket());
