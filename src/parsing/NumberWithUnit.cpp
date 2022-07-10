#include "NumberWithUnit.h"
#include "CommonPatterns.h"

LazyRegex NumberWithUnit::pattern(CommonPatterns::number +
                                  Units::pattern.bracket());
