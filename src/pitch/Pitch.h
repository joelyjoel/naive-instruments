#include "MidiNumber.h"
#include <string>
#include <vector>

/**
 * Useful stuff relating to musical pitch.
 */
class Pitch {
public:
  typedef enum { C = 0, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B } PitchClass;

  typedef enum {
    Natural = 0,
    Sharp = 1,
    Flat = -1,
    DoubleSharp = 2,
    DoubleFlat = -2
  } Accidental;

  static PitchClass pitchClass(int p) { return PitchClass(p % 12); }
  static int octave(int p) { return p / 12 - 1; }
  static int octave(float p) { return int(p / 12) - 1; }

  static const std::vector<const std::string> flatPitchNames;
  static const std::vector<const std::string> sharpPitchNames;
  static const std::string &
  pitchClassName(PitchClass pc, Accidental enharmonicPrefenence = Sharp) {
    if (enharmonicPrefenence == Flat || enharmonicPrefenence == DoubleFlat)
      return flatPitchNames[pc];
    else
      return sharpPitchNames[pc];
  }

  static const std::vector<const std::string> lilypondFlatNames;
  static const std::vector<const std::string> lilypondSharpNames;
  static const std::string &
  lilypondName(PitchClass pc, Accidental enharmonicPrefenence = Sharp) {
    if (enharmonicPrefenence == Flat || enharmonicPrefenence == DoubleFlat)
      return lilypondFlatNames[pc];
    else
      return lilypondSharpNames[pc];
  }

private:
  float p;

public:
  Pitch(float midiNumber) : p(midiNumber) {}
  Pitch(MidiNumber midiNumber) : p(midiNumber) {}
  PitchClass pitchClass() { return pitchClass(p); }
  int octave() { return octave(p); };

  std::string str() {
    // TODO: Support microtonal notation (cents?)
    return pitchClassName(pitchClass()) + std::to_string(octave());
  }

private:
  std::string lilypondName() { return lilypondName(pitchClass()); }
  std::string lilypondOctave() {
    if (octave() > 3)
      return std::string(octave() - 3, '\'');
    else
      return std::string(3 - octave(), ',');
  }

public:
  std::string lilypond() { return lilypondName() + lilypondOctave(); }
};

std::ostream &operator<<(std::ostream &out, Pitch &pitch);
