#pragma once

#include "../SignalShorthands.h"
#include "../core/Signal.h"
#include "WavWriter.h"
#include <string>

/**
 * Record a signal into a WAV file.
 */
void record( const std::string& outputFile, FrameStream<double>& signal, float duration );
void record( const std::string& outputFile, NaiveInstruments::SignalShorthands::mono signal, float duration );
void record( std::ostream& outputStream, FrameStream<double>& signal, float duration );
void record( std::ostream& outputStream, NaiveInstruments::SignalShorthands::mono, float duration );
