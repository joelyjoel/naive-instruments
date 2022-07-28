#include "../dependencies/catch.hpp"

#include "Pitch.h"

TEST_CASE("Pitch classes are correct") {
  REQUIRE(Pitch::C == 0);
  REQUIRE(Pitch::Db == 1);
  REQUIRE(Pitch::D == 2);
  REQUIRE(Pitch::Eb == 3);
  REQUIRE(Pitch::E == 4);
  REQUIRE(Pitch::F == 5);
  REQUIRE(Pitch::Gb == 6);
  REQUIRE(Pitch::G == 7);
  REQUIRE(Pitch::Ab == 8);
  REQUIRE(Pitch::A == 9);
  REQUIRE(Pitch::Bb == 10);
  REQUIRE(Pitch::B == 11);
}

TEST_CASE("Pitch classes") {
  REQUIRE(Pitch::pitchClass(C4) == Pitch::C);
  REQUIRE(Pitch::pitchClass(Db5) == Pitch::Db);
}

TEST_CASE("Pitch::octave") {
  REQUIRE(Pitch::octave(C4) == 4);
  REQUIRE(Pitch::octave(C5) == 5);
  REQUIRE(Pitch::octave(C_1) == -1);
  REQUIRE(Pitch::octave(Ab0) == 0);
  REQUIRE(Pitch::octave(B3) == 3);
  REQUIRE(Pitch::octave(B5) == 5);
}

TEST_CASE("Stringifying Pitch class intances") {
  REQUIRE(Pitch(C4).str() == "C4");
  REQUIRE(Pitch(C0).str() == "C0");
}

TEST_CASE("Lilypond pitch printing") { REQUIRE(Pitch(C4).lilypond() == "c'"); }
