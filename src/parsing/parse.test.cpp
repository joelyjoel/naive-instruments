
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "../../dependencies/catch.hpp"

#include "Parse.h"

unsigned int Factorial(unsigned int number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Parsing numbers", "[factorial]") {
  REQUIRE(Parse::number("42") == 42);
  REQUIRE(Parse::number(".42") == 0.42f);
  REQUIRE(Parse::number("1.42") == 1.42f);
  REQUIRE(Parse::number("-42") == -42);
  REQUIRE(Parse::number("-.42") == -0.42f);
  REQUIRE(Parse::number("-1.42") == -1.42f);
}
