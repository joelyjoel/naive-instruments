#include "../../dependencies/catch.hpp"

#include "RegularExpressionSources.h"
#include <regex>

using std::regex;

TEST_CASE("Parsing control signals", "[RegularExpressionSources]") {
  RegularExpressionSources sources;
  const regex re(sources.controlSequence);
  REQUIRE(regex_match("100Hz", re));
  REQUIRE(regex_match("440Hz____550Hz____", re));
  REQUIRE(regex_match("1s: 1 ~~~~ 0", re));
  REQUIRE(regex_match("1s: 1~~~~0", re));
}
