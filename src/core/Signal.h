#pragma once

#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

using std::shared_ptr, std::make_shared;

#include "FrameStream.h"

/**
 * Convenient alias for very freqeuent type.
 */
typedef shared_ptr<FrameStream<double>> sigarette;
