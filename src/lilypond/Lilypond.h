#include "../pitch/Pitch.h"

using std::vector, std::string;

class Lilypond {

  typedef enum {
    semibreve = 1,
    minim = 2,
    crotchet = 4,
    quaver = 8,
    semiquaver = 16,

  } ClassicalNoteDuration;

public:
  class Note {
  private:
    class Dot {
    public:
      bool tied;
      Pitch pitch;
      Dot(Pitch pitch) : pitch(pitch) {}
      string str() { return pitch.lilypond() + (tied ? "~" : ""); }
    };

  private:
    vector<Dot> dots;
    ClassicalNoteDuration _duration;

  public:
    ClassicalNoteDuration duration() { return _duration; }

  public:
    Note(MidiNumber pitch, ClassicalNoteDuration duration)
        : _duration(duration) {
      dots.push_back(Dot(pitch));
    }

    // Rest constructor
    Note(ClassicalNoteDuration duration) : _duration(duration) {}

  private:
    string durationStr() { return std::to_string(_duration); }

  public:
    string str() {
      if (dots.size() == 0) {
        return "r" + durationStr();
      } else if (dots.size() == 1) {
        return dots[0].str() + durationStr();
      } else {
        string out;
        for (auto dot : dots)
          out += dot.str() + " ";
        return "< " + out + ">";
      }
    }
  };

public:
  class Phrase {
    vector<Note> notes;

  public:
    string str() const {
      string out;
      for (auto note : notes) {
        out += note.str() + " ";
      }
      return "{ " + out + "}";
    }

    void appendNote(Lilypond::Note &note) { notes.push_back(note); }
    void appendNote(MidiNumber pitch, ClassicalNoteDuration duration) {
      Note note(pitch, duration);
      appendNote(note);
    }
    void appendNote(MidiNumber pitch) { appendNote(pitch, lastDuration()); }

    void appendRest(ClassicalNoteDuration duration) {
      Note note(duration);
      appendNote(note);
    }

  private:
    ClassicalNoteDuration defaultNoteDuration = semiquaver;
    ClassicalNoteDuration lastDuration() {
      return notes.size() ? notes[notes.size() - 1].duration()
                          : defaultNoteDuration;
    }
  };
};

std::ostream &operator<<(std::ostream &out, Lilypond::Phrase &phrase);
