#include "Lilypond.h"

std::ostream &operator<<(std::ostream &out, Lilypond::Phrase &phrase) {
  return out << phrase.str();
}
