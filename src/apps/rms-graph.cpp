#include "../lib.h"
#include <iostream>

int main(int argc, char **argv) {
  CommandLineArguments args(argc, argv);
  auto inputFile = args[0];

  RmsAsciGraph grapher;

  grapher.fromFile(std::cout, inputFile);
}
