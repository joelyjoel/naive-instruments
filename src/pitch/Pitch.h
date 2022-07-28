/**
 * Useful stuff relating to musical pitch.
 */
class Pitch {
public:
  typedef enum { C = 0, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B } PitchClass;

  PitchClass pitchClass(int p) { return PitchClass(p % 12); }
};
