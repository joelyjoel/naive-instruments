
#include "./readAudioFile.h"
#include "../../dependencies/catch.hpp"

TEST_CASE("can recognise a mono sample") {
  auto sample = readAudioFile("audio-source-files/Egg-Moww.wav");
  REQUIRE(sample->numberOfChannels == 1);
  REQUIRE(sample->sampleRate == 44100);
}
