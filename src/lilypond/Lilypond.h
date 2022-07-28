#include "../pitch/Pitch.h"
class Lilypond {

  typedef enum {
    semibreve = 1,
    minim = 2,
    crotchet = 4,
    quaver = 8,
    semiquaver = 16,

  } ClassicalNoteDuration;

  class Note {
  private:
    MidiNumber pitch;
    ClassicalNoteDuration duration;

  public:
    Note(MidiNumber pitch, ClassicalNoteDuration duration)
        : pitch(pitch), duration(duration) {}
  };
};
