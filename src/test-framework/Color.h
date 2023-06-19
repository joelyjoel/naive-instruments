#include <string>

class TextColor
{
    // typedef enum {
    // None = -1,
    // Black = 0,
    // Red,
    // Green,
    // Yellow,
    // Blue,
    // Magenta,
    // Cyan,
    // White
    //} ColorValue;

public:
    static const std::string reset()
    {
        return "\033[0m";
    }
    static const std::string red()
    {
        return "\033[31m";
    };
    static const std::string green()
    {
        return "\033[32m";
    };
    static const std::string yellow()
    {
        return "\033[33m";
    };
};
