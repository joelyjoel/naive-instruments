#include "../../dependencies/catch.hpp"
#include <regex>

#include "LazyRegex.h"
using std::regex_match;

TEST_CASE("Constructing a regex lazily from a string literal") {

  LazyRegex pattern("foo|bar");

  REQUIRE(regex_match("foo", *pattern) == true);
  REQUIRE(regex_match("bar", *pattern) == true);
  REQUIRE(regex_match("baz", *pattern) == false);
}

TEST_CASE("Appending a source string to a LazyRegex") {
  LazyRegex pattern1("foo");

  LazyRegex pattern2 = pattern1 + "|bar";

  REQUIRE(regex_match("foo", *pattern2) == true);
  REQUIRE(regex_match("bar", *pattern2) == true);
  REQUIRE(regex_match("baz", *pattern2) == false);
}
TEST_CASE("Prepending a source string to a LazyRegex") {
  LazyRegex pattern1("foo");

  LazyRegex pattern2 = "bar|" + pattern1;

  REQUIRE(regex_match("foo", *pattern2) == true);
  REQUIRE(regex_match("bar", *pattern2) == true);
  REQUIRE(regex_match("baz", *pattern2) == false);
}
TEST_CASE("Concatenating two LazyRegexs") {
  LazyRegex p1("fo"), p2("o+");
  LazyRegex pattern = p1 + p2;

  REQUIRE(regex_match("foo", *pattern) == true);
  REQUIRE(regex_match("fooo", *pattern) == true);
  REQUIRE(regex_match("foooo", *pattern) == true);
  REQUIRE(regex_match("bar", *pattern) == false);
}

TEST_CASE("Operator overload for disjunction of LazyRegexs") {
  LazyRegex p1("foo");
  LazyRegex p2("bar");
  LazyRegex pattern = p1 | p2;

  REQUIRE(regex_match("foo", *pattern) == true);
  REQUIRE(regex_match("bar", *pattern) == true);
  REQUIRE(regex_match("baz", *pattern) == false);
}

TEST_CASE("making a LazyRegex optional") {
  LazyRegex p1("round ");
  LazyRegex pattern = "a " + p1.optional() + "circle";

  REQUIRE(regex_match("a circle", *pattern) == true);
  REQUIRE(regex_match("a round circle", *pattern) == true);
  REQUIRE(regex_match("a square circle", *pattern) == false);
}

TEST_CASE("Kleene closure of a LazyRegex") {
  LazyRegex p1("foo");
  LazyRegex pattern = p1.kleene();

  REQUIRE(regex_match("", *pattern) == true);
  REQUIRE(regex_match("foo", *pattern) == true);
  REQUIRE(regex_match("foofoo", *pattern) == true);
  REQUIRE(regex_match("foofoofoo", *pattern) == true);
  REQUIRE(regex_match("fooofoofoo", *pattern) == false);
  REQUIRE(regex_match("bar", *pattern) == false);
}
