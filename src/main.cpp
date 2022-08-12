#include "commands/BoopCommand.h"
#include "commands/FMCommand.h"
#include "commands/FilterCommand.h"
#include "commands/GraphCommand.h"
#include "commands/HelloCommand.h"
#include "commands/MetronomeCommand.h"
#include "commands/MixCommand.h"
#include "commands/NoiseCommand.h"
#include "commands/OscCommand.h"
#include "commands/RandomCommand.h"
#include "commands/RulerCommand.h"
#include "commands/SliceCommand.h"
#include "commands/ZxSelectCommand.h"
#include "lib.h"
#include <string>

int main(int argc, char **argv) {
  MainArgs args(argc - 1, argv + 1);

  if (argc == 1) {
    // TODO: use class FrontPage
    std::cout << "Naive Instruments CLI.\n";
    return 0;
  }

  // TODO: Migrate zero crossing utils as units in the sample interface

  // TODO: Use a class for switching commands
  std::string command = argv[1];
  if (command == "help") {
    std::cout << "No help has been written yet!\n";
    return 0;
  } else if (command == "hello") {
    HelloCommand app(args.argc, args.argv);
    app.run();
  } else if (command == "slice") {
    SliceCommand app(args);
    app();
  } else if (command == "graph") {
    GraphCommand app(args);
    app();
  } else if (command == "ruler") {
    RulerCommand app(args);
    app();
  } else if (command == "mix") {
    MixCommand app(args.argc, args.argv);
    app();
  } else if (command == "osc") {
    OscCommand app(args.argc, args.argv);
    app();
  } else if (command == "boop") {
    BoopCommand app(args.argc, args.argv);
    app();
  } else if (command == "filter") {
    FilterCommand app(args.argc, args.argv);
    app();
  } else if (command == "noise") {
    NoiseCommand app(args.argc, args.argv);
    app();
  } else if (command == "random") {
    RandomCommand app(args);
    app();
  } else if (command == "zx-select") {
    // TODO: Deprecate command in favour of special units?
    ZxSelectCommand app(args);
    app();
  } else if (command == "fm") {
    FMCommand app(args);
    app();
  } else if (command == "metronome") {
    MetronomeCommand app(args.argc, args.argv);
    app();
  } else {
    std::cout << "Unknown command: " << command << "\n";
    return 1;
  }
}
