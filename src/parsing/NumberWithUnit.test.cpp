
#include "NumberWithUnit.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("NumberWithUnit::pattern parses plenty of cases") {
  auto &pattern = NumberWithUnit::pattern;

  std::cout << "NumberWithUnit::pattern = " << pattern.src() << "\n";

  REQUIRE(pattern.test("1Hz"));
  REQUIRE(pattern.test("99%"));
  REQUIRE(pattern.test("100"));
  REQUIRE(pattern.test("-.45ms"));
}
