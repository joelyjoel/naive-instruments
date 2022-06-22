
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "../../dependencies/catch.hpp"

#include "Parse.h"

unsigned int Factorial(unsigned int number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Parsing numbers", "[Parse]") {
  REQUIRE(Parse::number("42") == 42);
  REQUIRE(Parse::number(".42") == 0.42f);
  REQUIRE(Parse::number("1.42") == 1.42f);
  REQUIRE(Parse::number("-42") == -42);
  REQUIRE(Parse::number("-.42") == -0.42f);
  REQUIRE(Parse::number("-1.42") == -1.42f);
}
TEST_CASE("Parsing units", "[Parse]") {
  REQUIRE(Parse::unit("s") == Units::seconds);
  REQUIRE(Parse::unit("ms") == Units::milliseconds);
}

TEST_CASE("Parsing numbers with units", "[Parse]") {
  REQUIRE(Parse::numberWithUnit("12s").number == 12);
  REQUIRE(Parse::numberWithUnit("12s").unit == Units::seconds);
  REQUIRE(Parse::numberWithUnit("12 seconds").number == 12);
  REQUIRE(Parse::numberWithUnit("12 seconds").unit == Units::seconds);
  REQUIRE(Parse::numberWithUnit("12").unit == Units::noUnit);
}

TEST_CASE("Parsing times with different units", "[Parse]") {
  REQUIRE(Parse::time("1") == 1);
  REQUIRE(Parse::time("1s") == 1.0);
  REQUIRE(Parse::time("100ms") == 0.1f);
}
