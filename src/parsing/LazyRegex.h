#include <regex>
#include <string>

using std::string, std::regex;

/**
 * Regex class for lazy people and computers.
 *
 * Lazy in 2 ways:
 *  - It won't construct the regex until you try to use it.
 *  - It adds some conveniences that make using regex a bit more like js.
 */
class LazyRegex {

private:
  const string _src;
  const regex *_pattern = nullptr;

public:
  LazyRegex(const string &src) : _src(src) {}

  /**
   * Get the string source of the regex
   */
  const string &src() const { return _src; }
  const regex &pattern() {
    if (_pattern == nullptr) {
      _pattern = new regex(src());
      return *_pattern;
    } else
      return *_pattern;
  }

  /**
   * Operator shortcut for getting the regex object from the LazyRegex
   * container.
   */
  const regex &operator*() { return pattern(); }

  // Functions for regex composition

  LazyRegex operator+(const string &operand) const { return src() + operand; }

  LazyRegex operator+(const LazyRegex &operand) const {
    return src() + operand.src();
  }
};

LazyRegex operator+(const string &a, const LazyRegex &b);
