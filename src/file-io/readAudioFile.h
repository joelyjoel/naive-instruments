#include "../core/Sample.h"
#include <memory>
#include <sndfile.hh>

std::shared_ptr<Sample<double>> readAudioFile(const std::string &filename);
