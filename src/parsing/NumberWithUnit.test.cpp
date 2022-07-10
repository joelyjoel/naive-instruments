
#include "NumberWithUnit.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("NumberWithUnit::pattern parses plenty of cases") {
  auto &pattern = NumberWithUnit::pattern;

  REQUIRE(pattern.test("1Hz"));
  REQUIRE(pattern.test("99%"));
  REQUIRE(pattern.test("100"));
  REQUIRE(pattern.test("-.45ms"));
}

TEST_CASE("NumberWithUnit::parse ~~ Parsing numbers with units", "[Parse]") {
  REQUIRE((*NumberWithUnit::parse("12s")).number == 12);
  REQUIRE(NumberWithUnit::parse("12s")->unit == Units::seconds);
  REQUIRE(NumberWithUnit::parse("12 seconds")->number == 12);
  REQUIRE(NumberWithUnit::parse("12 seconds")->unit == Units::seconds);
  REQUIRE(NumberWithUnit::parse("12")->unit == Units::noUnit);
}
