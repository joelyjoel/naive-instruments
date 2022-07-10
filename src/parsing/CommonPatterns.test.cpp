#include "../../dependencies/catch.hpp"

#include "CommonPatterns.h"
#include <string>
#include <vector>

using std::string, std::vector;

TEST_CASE("CommonPatterns::naturalNumber accepts simple positive integers") {
  // Positive assertions
  REQUIRE(CommonPatterns::naturalNumber.test("99"));
  REQUIRE(CommonPatterns::naturalNumber.test("0"));

  // Negative assertions
  REQUIRE(!CommonPatterns::naturalNumber.test(""));
  REQUIRE(!CommonPatterns::naturalNumber.test("-1"));
  REQUIRE(!CommonPatterns::naturalNumber.test("1.1"));
  REQUIRE(!CommonPatterns::naturalNumber.test(".1"));
  REQUIRE(!CommonPatterns::naturalNumber.test(" 1.1"));
  REQUIRE(!CommonPatterns::naturalNumber.test("cat"));
  REQUIRE(!CommonPatterns::naturalNumber.test("99cat"));
}

TEST_CASE("CommonPatterns::integer accepts only zero and positive and negative "
          "numbers") {
  REQUIRE(CommonPatterns::integer.test("0"));
  REQUIRE(CommonPatterns::integer.test("1"));
  REQUIRE(CommonPatterns::integer.test("-1"));
  REQUIRE(CommonPatterns::integer.test("999"));
  REQUIRE(CommonPatterns::integer.test("-999"));

  // Negative assertions
  REQUIRE(!CommonPatterns::integer.test("-999.0"));
  REQUIRE(!CommonPatterns::integer.test("0.9"));
}

TEST_CASE("CommonPaterns:unsignedDecimal accepts unsigned numbers with decimal "
          "point") {
  REQUIRE(CommonPatterns::unsignedDecimal.test("0.0"));
  REQUIRE(CommonPatterns::unsignedDecimal.test("100.0"));
  REQUIRE(CommonPatterns::unsignedDecimal.test("3.14"));

  REQUIRE(!CommonPatterns::unsignedDecimal.test("-100.0"));
  REQUIRE(!CommonPatterns::unsignedDecimal.test("100"));
  REQUIRE(!CommonPatterns::unsignedDecimal.test(".2"));
}

TEST_CASE("CommonPaterns:unsignedPointNumber accepts unsigned numbers that "
          "begin with decimal "
          "point") {
  REQUIRE(!CommonPatterns::unsignedPointNumber.test("0.0"));
  REQUIRE(!CommonPatterns::unsignedPointNumber.test("100.0"));
  REQUIRE(!CommonPatterns::unsignedPointNumber.test("3.14"));

  REQUIRE(!CommonPatterns::unsignedPointNumber.test("-100.0"));
  REQUIRE(!CommonPatterns::unsignedPointNumber.test("100"));
  REQUIRE(CommonPatterns::unsignedPointNumber.test(".2"));
  REQUIRE(CommonPatterns::unsignedPointNumber.test(".02"));
  REQUIRE(CommonPatterns::unsignedPointNumber.test(".0"));
}

TEST_CASE("number accepts any number") {
  vector<string> validNumberStrings = {"0",  "10",    "-0",   "-10", "0.0",
                                       ".0", ".0123", "-.55", "-.45"};
  for (auto &str : validNumberStrings)
    REQUIRE(CommonPatterns::number.test(str));
}

TEST_CASE(
    "CommonPatterns::word accepts any sequence of alphanumeric characters") {
  REQUIRE(CommonPatterns::word.test("100"));
  REQUIRE(CommonPatterns::word.test("banana"));
  REQUIRE(CommonPatterns::word.test("oontebk249d49xd"));

  // Negative tests
  REQUIRE(!CommonPatterns::word.test("."));
  REQUIRE(!CommonPatterns::word.test("%"));
  REQUIRE(!CommonPatterns::word.test("hello world"));
}
