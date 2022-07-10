#include "../../dependencies/catch.hpp"

#include "ControlString.h"

TEST_CASE("ControlString::TempoInstruction::pattern") {
  REQUIRE(ControlString::TempoInstruction::pattern.test("106bpm:"));
  REQUIRE(ControlString::TempoInstruction::pattern.test("1Hz:"));
  REQUIRE(ControlString::TempoInstruction::pattern.test(".25s:"));
}

TEST_CASE("ControlSTring::ValueInstruction::pattern") {
  REQUIRE(ControlString::ValueInstruction::pattern.test("100Hz"));
  REQUIRE(ControlString::ValueInstruction::pattern.test("54"));
  REQUIRE(!ControlString::ValueInstruction::pattern.test("99s:"));
}

TEST_CASE("ControlString::SustainStepInstruction::pattern") {
  REQUIRE(ControlString::SustainStepInstruction::pattern.test("~"));
  REQUIRE(ControlString::SustainStepInstruction::pattern.test("_"));
}

TEST_CASE("ControlString::anyInstructionPattern") {
  REQUIRE(ControlString::anyInstructionPattern.test("106bpm:"));
  REQUIRE(ControlString::anyInstructionPattern.test("1Hz:"));
  REQUIRE(ControlString::anyInstructionPattern.test(".25s:"));
  REQUIRE(ControlString::anyInstructionPattern.test("~"));
  REQUIRE(ControlString::anyInstructionPattern.test("_"));
  REQUIRE(ControlString::anyInstructionPattern.test("100Hz"));
  REQUIRE(ControlString::anyInstructionPattern.test("54"));
}

TEST_CASE("ControlString::pattern") {
  REQUIRE(ControlString::pattern.test("1~~~0"));
  REQUIRE(ControlString::pattern.test("100_ 200_ 100_ 200_"));
}
