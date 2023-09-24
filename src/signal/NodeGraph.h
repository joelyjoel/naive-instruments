#include "Signal.h"
#include <boost/algorithm/string.hpp>
#include <memory>
#include <string>
#include <vector>

/**
 * A class for representing graphs using a plaintext notations. These are intended to be used to show the internal
 * structure of signal processes, but they could be repurposed for other applications.
 */
class NodeGraph
{
protected:
    /** The name of the node */
    const std::string head;

    std::vector<std::shared_ptr<NodeGraph>> inputs;

public:
    NodeGraph( std::string head )
    : head( head )
    {
    }

    void addInput( std::shared_ptr<NodeGraph> input )
    {
        inputs.push_back( input );
    }

    std::string stringify()
    {
        std::string shorthand = stringifyInline();
        // TODO: Max width should be configurable
        if ( shorthand.size() < 80 )
            return shorthand;
        else
            return stringifyMultiline();
    }

    std::string stringifyInline()
    {
        std::string str = head + "(";
        // TODO: Could refactor to use array methods
        for ( int i = 0; i < inputs.size(); ++i )
        {
            if ( i != 0 )
                str += ", ";
            str += inputs[i]->stringify();
        }
        str += ")";
        return str;
    }

    std::string stringifyMultiline()
    {
        std::string str = head + ":";
        for ( auto input : inputs )
            str += "\n" + indentInPlace( input->stringifyMultiline() );
        return str;
    }

private:
    static std::string indentInPlace( std::string str )
    {
        std::string prefix = " └";
        std::string spaces = "  ";
        boost::replace_all( str, "\n", "\n" + spaces );
        return prefix + str;
    }


    // TODO: add parsing methods
};
