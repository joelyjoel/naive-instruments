#include "MidiNumber.h"
#include <string>
#include <vector>

/**
 * Useful stuff relating to musical pitch.
 */
class Pitch {
public:
  typedef enum { C = 0, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B } PitchClass;
  static const std::vector<const std::string> flatPitchNames;
  static const std::vector<const std::string> sharpPitchNames;

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

  static const std::string &
  pitchClassName(PitchClass pc, Accidental enharmonicPrefenence = Sharp) {
    if (enharmonicPrefenence == Flat || enharmonicPrefenence == DoubleFlat)
      return flatPitchNames[pc];
    else
      return sharpPitchNames[pc];
  }

private:
  float p;

public:
  Pitch(MidiNumber midiNumber) : p(midiNumber) {}
  PitchClass pitchClass() { return pitchClass(p); }
  int octave() { return octave(p); };

  std::string str() {
    // TODO: Support microtonal notation (cents?)
    return pitchClassName(pitchClass()) + std::to_string(octave());
  }
};

std::ostream &operator<<(std::ostream &out, Pitch &pitch);
