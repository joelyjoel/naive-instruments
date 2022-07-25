#pragma once

#include "WAV_HEADER.h"
#include <fstream>
#include <iostream>
#include <string>

#include "../core.h"

typedef struct {
  double left;
  double right;
} StereoFrame;

class WavReader {
  std::istream &in;

private:
  WAV_HEADER header;
  void readHeader() {
    // TODO: How to detect failure?
    in.read(reinterpret_cast<char *>(&header), sizeof(header));

    assertStandardCDAudio();
  }

  void assertStandardCDAudio() {
    assert(header.AudioFormat == 1);
    assert(header.Subchunk1Size == 16);
    assert(header.Subchunk2ID[0] == 'd');
    assert(header.Subchunk2ID[1] == 'a');
    assert(header.Subchunk2ID[2] == 't');
    assert(header.Subchunk2ID[3] == 'a');
    assert(header.bitsPerSample == 16);
  }

  int numberOfChannels() { return header.NumOfChan; }

public:
  WavReader(const std::string &filePath)
      : in(*new std::ifstream(filePath, std::ios::binary)) {
    // TODO: Check the file exists
    readHeader();
  }

  WavReader(std::istream &inputStream) : in(inputStream) { readHeader(); }

  StereoFrame readNextFrame() {
    if (numberOfChannels() == 2) {
      int16_t l16bit, r16bit;
      in.read(reinterpret_cast<char *>(&l16bit), sizeof(l16bit));
      in.read(reinterpret_cast<char *>(&r16bit), sizeof(r16bit));
      return {int16ToDouble(l16bit), int16ToDouble(r16bit)};
    } else if (numberOfChannels() == 1) {
      int16_t sig16bit;
      in.read(reinterpret_cast<char *>(&sig16bit), sizeof(sig16bit));
      double signal = int16ToDouble(sig16bit);
      return {signal, signal};
    } else {
      std::cerr << "Expected mono or stereo audio, got " << numberOfChannels()
                << " channels\n";
      throw 1;
    }
  }

private:
  double int16ToDouble(int16_t x) { return double(x) / (INT16_MAX * .5); }

public:
  int sampleRate() { return header.SamplesPerSec; }
  int numberOfFrames() {
    return header.Subchunk2Size / (numberOfChannels() * sizeof(int16_t));
  }
  float duration() { return float(numberOfFrames()) / float(sampleRate()); }

  static MonoBuffer *readMonoFile(const std::string &filePath) {
    std::ifstream inputStream(filePath, std::ios::binary);
    return readStream(inputStream);
  }

  static MonoBuffer *readStream(std::istream &inputStream) {
    WavReader file(inputStream);
    int numberOfFrames = file.numberOfFrames();
    MonoBuffer &buffer = *(new MonoBuffer(numberOfFrames));
    for (int i = 0; i < numberOfFrames; ++i) {
      double y = file.readNextFrame().left;
      buffer[i] = y;
    }

    return &buffer;
  }
};
