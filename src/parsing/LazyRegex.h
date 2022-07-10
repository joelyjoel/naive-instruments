#pragma once
#include <exception>
#include <iostream>
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
      try {
        _pattern = new regex(src());
        return *_pattern;
      } catch (std::exception err) {
        std::cerr << "There was a problem creating a LazyRegex from source: "
                  << src() << "\n";
        throw err;
      }
    } else
      return *_pattern;
  }

  /**
   * Operator shortcut for getting the regex object from the LazyRegex
   * container.
   */
  const regex &operator*() { return pattern(); }

  bool test(const string &str) { return std::regex_match(str, pattern()); }

  // Functions for regex composition

  LazyRegex operator+(const string &operand) const { return src() + operand; }

  LazyRegex operator+(const LazyRegex &operand) const {
    return src() + operand.src();
  }

  LazyRegex bracket() const { return "(?:" + src() + ")"; }

  LazyRegex capture() const { return "(" + src() + ")"; }

  LazyRegex optional() const { return bracket() + "?"; }
  LazyRegex disjunction(const LazyRegex &operand) const {
    return bracket() + "|" + operand.bracket();
  }
  LazyRegex operator|(const LazyRegex &operand) const {
    return disjunction(operand);
  }

  LazyRegex kleene() const { return bracket() + "*"; }
};

LazyRegex operator+(const string &a, const LazyRegex &b);
