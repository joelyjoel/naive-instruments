#include <string>

enum Unit {
  unknownUnit,
  noUnit,
  ms,
  second,
  percentage,
  Hz,
  dB,
  zeroCrossings,
  semiquavers,
  quavers,
  crotchets
};

Unit parseUnit(std::string str);
