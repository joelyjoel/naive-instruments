#pragma once

#define TODO 1000

typedef struct {
  double left;
  double right;
} StereoFrame;

#include "core/Errors.h"
#include "core/Hopefully.h"
#include "core/MonoBuffer.h"
#include "core/Patch.h"
#include "core/Signal.h"
#include "generative/Random.h"
