#pragma once

#include "../core/Signal.h"
#include "WavWriter.h"
#include <string>

/**
 * Record a signal into a WAV file.
 */
void record(const std::string &outputFile, Signal<double> &signal,
            float duration);

void record(std::ostream &outputStream, Signal<double> &signal, float duration);
