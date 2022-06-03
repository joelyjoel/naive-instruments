#include "../lib.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  CommandLineArguments args(argc, argv);

  for (int i = 0; i < args.numberOfPositionalArgs(); ++i) {
    auto inputFile = args[i];

    RmsAsciGrapher grapher;

    int width = args.integer("width", 80);
    int height = args.integer("height", 9);

    RectangleBuffer<std::string> canvas(width, height);

    grapher.fromFile(canvas, inputFile);

    canvas.stream(std::cout);
  }
}
