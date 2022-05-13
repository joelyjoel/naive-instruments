#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>

class WavWriter {
  typedef struct WAV_HEADER {
    /* RIFF Chunk Descriptor */
    uint8_t RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
    uint32_t ChunkSize;                     // RIFF Chunk Size
    uint8_t WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t fmt[4] = {'f', 'm', 't', ' '}; // FMT header
    uint32_t Subchunk1Size = 16;           // Size of the fmt chunk
    uint16_t AudioFormat = 1; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
                              // Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t NumOfChan = 2;   // Number of channels 1=Mono 2=Sterio
    uint32_t SamplesPerSec = 41000;   // Sampling Frequency in Hz
    uint32_t bytesPerSec = 41000 * 2; // bytes per second
    uint16_t blockAlign = 4;          // 2=16-bit mono, 4=16-bit stereo
    uint16_t bitsPerSample = 16;      // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
    uint32_t Subchunk2Size;                        // Sampled data length
  } wav_hdr;

  std::ofstream out;

public:
  WavWriter(std::string outfile, int numberOfFrames)
      : out(outfile, std::ios::binary) {

    // Stereo 16-bit
    int dataSize = 2 * sizeof(int16_t) * numberOfFrames;

    WAV_HEADER header;

    header.Subchunk2Size = dataSize;
    header.ChunkSize = dataSize + sizeof(header) - 8;
    // -8 because of the "RIFF{uint32_t ChunkSize}" at the beginning

    out.write(reinterpret_cast<const char *>(&header), sizeof(header));
  }

  void write(int left, int right) {
    int16_t l16bit = left;
    int16_t r16bit = right;
    out.write(reinterpret_cast<const char *>(&l16bit), sizeof(l16bit));
    out.write(reinterpret_cast<const char *>(&r16bit), sizeof(r16bit));
  }

  void write(int value) { write(value, value); }
  void write(double value) { write(doubleToInt16_t(value)); }
  void write(double left, double right) {
    write(doubleToInt16_t(left), doubleToInt16_t(right));
  }

  int16_t doubleToInt16_t(double val) {
    // return 0;
    return INT16_MAX * val * .5;
  }
};
