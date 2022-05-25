#pragma once

#include "../lib.h"
#include "./RMS.h"
#include <iostream>
#include <string>

class RmsAsciGrapher {
  const std::string charsInAscendingOrderOfLoudness = " -~sS#%!";

public:
  int width = WindowDimensions::width();
  int height = WindowDimensions::height();

public:
  void fromFile(std::ostream &out, const std::string &filePath) {
    WavReader file(filePath);
    Sampler sampler(filePath);

    RMS loudness;
    loudness.windowSize = file.numberOfFrames() / width;
    if (loudness.windowSize < 1) {
      std::cerr << "Too short\n";
      throw 66;
    }

    loudness << sampler;

    RectangleBuffer<std::string> canvas(width, height);
    canvas.fill(" ");

    RectangularLineTool pen1(canvas);
    RectangularLineTool pen2(canvas);
    pen1.moveTo(0, canvas.height / 2);

    for (int window = 0; window < width; ++window) {
      double rms = loudness.nextWindow();

      int index = int(rms * float(charsInAscendingOrderOfLoudness.length()));
      char c = charsInAscendingOrderOfLoudness[c];

      float y = rms * float(canvas.height);
      float x = float(canvas.width) * window / width;

      pen1.lineTo(x, canvas.height - y);
    }

    TextTool labeller(canvas);
    labeller.moveTo(0, 0);
    labeller.write(filePath);

    out << canvas;
  }
};
