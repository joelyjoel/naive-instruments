#include "../core.h"
#include <vector>

using std::cerr;
using std::vector, std::string;

// TODO: Refactor as two classes. A rhythm class, and a RhythmPlayer :
// Signal<bool> class

class Rhythm : public Signal<bool> {

public:
  SignalInput<double> &bpm = addInput<double>(139.0);

  Rhythm(vector<float> durations) : durations(durations) {}

private:
  vector<float> durations;
  double elapsed = 0;
  int index = 0;

  const double k = 1.0 / (60.0 * sampleRate);

protected:
  void action() override {
    elapsed += bpm() * k;
    if (elapsed > durations[index]) {
      out(true);
      do {
        elapsed -= durations[index];
        index = (index + 1) % durations.size();
      } while (elapsed > durations[index]);
    } else
      out(false);
  }

public:
  static Rhythm *fromBinaryString(const string &str) {
    vector<float> durations = {0};
    for (int i = 0; i < str.size(); ++i) {
      char c = str[i];

      if (c == '0' || c == '.')
        durations[durations.size() - 1] += .5;
      else if (c == '1' || c == '!')
        durations.push_back(.5);
      else {
        cerr << "Unexpected char '" << c << "' while parsing rhythm\n";
        throw 1;
      }
    }
    return new Rhythm(durations);
  }

public:
  std::ostream &describe(std::ostream &out) {
    for (float duration : durations)
      out << duration << "b ";
    return out;
  }
};

std::ostream &operator<<(std::ostream &out, Rhythm &rhythm);
