#include "../core/Sample.h"
#include <memory>
#include <sndfile.hh>

void writeAudioFile(const std::string &filename, Sample<double> &sample);
