#include "./CommandLineArguments.h"

std::ostream& operator<<( std::ostream& os, const CommandLineArguments& args )
{
    os << "Positional args:\n";
    for ( int i = 0; i < args.positionalArguments.size(); ++i )
        os << "  " << args.positionalArguments[i] << "\n";

    os << "Named Args:\n";
    for ( auto const& [key, val] : args.namedArgs )
        os << "  " << key << " -> " << val << "\n";

    return os;
}
