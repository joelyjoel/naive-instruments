#pragma once

#include "WAV_HEADER.h"
#include <fstream>
#include <string>

typedef struct {
  double left;
  double right;
} StereoFrame;

class WavReader {
  std::ifstream in;

private:
  WAV_HEADER header;
  void readHeader() {
    in.read(reinterpret_cast<char *>(&header), sizeof(header));

    assertStandardCDAudio();
  }

  void assertStandardCDAudio() {
    // TODO: implement!
  }

public:
  WavReader(const std::string &filePath) : in(filePath, std::ios::binary) {
    readHeader();
  }

  StereoFrame readNextFrame() {
    int16_t l16bit, r16bit;
    in.read(reinterpret_cast<char *>(&l16bit), sizeof(l16bit));
    in.read(reinterpret_cast<char *>(&r16bit), sizeof(r16bit));
    return {int16ToDouble(l16bit), int16ToDouble(r16bit)};
  }

private:
  double int16ToDouble(int16_t x) { return double(x) / (INT16_MAX * .5); }

public:
  int numberOfFrames() { return header.Subchunk2Size / (2 * sizeof(int16_t)); }
};
