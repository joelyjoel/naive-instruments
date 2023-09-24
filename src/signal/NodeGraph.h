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

    std::string toString()
    {
        std::string shorthand = toInlineString();
        // TODO: Max width should be configurable
        if ( shorthand.size() < 80 )
            return shorthand;
        else
            return toMultilineString();
    }

private:
    std::string toInlineString()
    {
        std::string str = head;
        if ( inputs.size() > 0 )
        {
            str += "(";
            // TODO: Could refactor to use array methods
            for ( int i = 0; i < inputs.size(); ++i )
            {
                if ( i != 0 )
                    str += ", ";
                str += inputs[i]->toInlineString();
            }
            str += ")";
        }
        return str;
    }

    std::string toMultilineString()
    {
        std::string str = head;
        if ( inputs.size() > 0 )
        {
            str += ":";
            for ( auto input : inputs )
                str += "\n" + indentInPlace( input->toString() );
        }
        return str;
    }

    static std::string indentInPlace( std::string str )
    {
        std::string prefix = "  ";
        std::string spaces = "  ";
        boost::replace_all( str, "\n", "\n" + spaces );
        return prefix + str;
    }


    // TODO: add parsing methods
};
