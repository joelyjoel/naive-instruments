
#include "./SignalString.h"

void operator<<(SignalInput<double> &input, const std::string &str) {
  input << SignalString::parse(str);
}
