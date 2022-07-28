#include "Pitch.h"

const std::vector<const std::string> Pitch::flatPitchNames(
    {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"});
const std::vector<const std::string> Pitch::sharpPitchNames(
    {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"});

std::ostream &operator<<(std::ostream &out, Pitch &pitch) {
  return out << pitch.str();
}
