#pragma once

#include "NaiveInstrument.h"
#include "WavWriter.h"
#include <string>

/**
 * Record a signal into a WAV file.
 */
void record(const std::string &outputFile, NaiveInstrument<double> &signal,
            float duration);
