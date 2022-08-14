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
  static Rhythm *parse(const string &str) {
    // TODO: Use a dictionary for named rhythms instead?
    if (str == "son" || str == "son32")
      return parse("1001001000101000");
    else if (str == "rhumba" || str == "rhumba32")
      return parse("1001000100101000");
    else if (str == "son23")
      return parse("0010100010010010");
    else if (str == "rhumba23")
      return parse("0010100010010001");
    else if (str == "+")
      return parse("x8 0+");
    else if (str == "e")
      return parse("x16 0100");
    else if (str == "u")
      return parse("x16 0001");

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
