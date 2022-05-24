#include "core/MonoBuffer.h"
#include "core/NaiveInstrument.h"
#include "core/Patch.h"
#include "core/Socket.h"
#include "core/constants.h"
#include "file-io/WavReader.h"
#include "file-io/WavWriter.h"
#include "file-io/record.h"

// Instruments
#include "instruments/AHD.h"
#include "instruments/Add.h"
#include "instruments/BreakpointEnvelope.h"
#include "instruments/BufferWriter.h"
#include "instruments/FixedPipe.h"
#include "instruments/Floor.h"
#include "instruments/LFO.h"
#include "instruments/Multiply.h"
#include "instruments/Osc.h"
#include "instruments/Pitch.h"
#include "instruments/Ramp.h"
#include "instruments/Sampler.h"
#include "instruments/UnsignedSaw.h"
#include "instruments/Wavetable.h"
#include "instruments/ZeroCrossingDetector.h"
