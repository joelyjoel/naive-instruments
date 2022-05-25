#include "../lib.h"
#include <iostream>

int main(int argc, char **argv) {
  CommandLineArguments args(argc, argv);

  for (int i = 0; i < args.numberOfPositionalArgs(); ++i) {
    auto inputFile = args[i];

    RmsAsciGrapher grapher;

    grapher.width = args.integer("width", grapher.width);
    grapher.height = args.integer("height", 9);

    grapher.fromFile(std::cout, inputFile);
  }
}
