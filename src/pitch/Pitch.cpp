#include "Pitch.h"

const std::vector<const std::string> Pitch::flatPitchNames(
    {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"});
const std::vector<const std::string> Pitch::sharpPitchNames(
    {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"});

const std::vector<const std::string> Pitch::lilypondFlatNames(
    {"c", "des", "d", "ees", "e", "f", "ges", "g", "aes", "a", "bes", "b"});

const std::vector<const std::string> Pitch::lilypondSharpNames(
    {"c", "cis", "d", "dis", "e", "f", "fis", "g", "gis", "a", "ais", "b"});

std::ostream &operator<<(std::ostream &out, Pitch &pitch) {
  return out << pitch.str();
}
