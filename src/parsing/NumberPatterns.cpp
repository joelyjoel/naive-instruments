#include "NumberPatterns.h"

LazyRegex NumberPatterns::naturalNumber( "\\d+" );

LazyRegex NumberPatterns::integer( "[-+]? ?" + naturalNumber );

LazyRegex NumberPatterns::unsignedDecimal( naturalNumber + "\\." + naturalNumber );
LazyRegex NumberPatterns::unsignedPointNumber( "\\." + naturalNumber );

LazyRegex NumberPatterns::number( "-?" + ( naturalNumber | unsignedDecimal | unsignedPointNumber ).bracket() );
