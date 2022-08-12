#include "commands/BoopApp.h"
#include "commands/FMApp.h"
#include "commands/FilterApp.h"
#include "commands/GraphApp.h"
#include "commands/HelloApp.h"
#include "commands/MetronomeApp.h"
#include "commands/MixApp.h"
#include "commands/NoiseApp.h"
#include "commands/OscApp.h"
#include "commands/RandomApp.h"
#include "commands/RulerApp.h"
#include "commands/SliceApp.h"
#include "commands/ZxSelectApp.h"
#include "lib.h"
#include <string>

int main(int argc, char **argv) {
  MainArgs args(argc - 1, argv + 1);

  if (argc == 1) {
    // TODO: use class FrontPage : public App
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
    HelloApp app(args.argc, args.argv);
    app.run();
  } else if (command == "slice") {
    SliceApp app(args);
    app();
  } else if (command == "graph") {
    GraphApp app(args);
    app();
  } else if (command == "ruler") {
    RulerApp app(args);
    app();
  } else if (command == "mix") {
    MixApp app(args.argc, args.argv);
    app();
  } else if (command == "osc") {
    OscApp app(args.argc, args.argv);
    app();
  } else if (command == "boop") {
    BoopApp app(args.argc, args.argv);
    app();
  } else if (command == "filter") {
    FilterApp app(args.argc, args.argv);
    app();
  } else if (command == "noise") {
    NoiseApp app(args.argc, args.argv);
    app();
  } else if (command == "random") {
    RandomApp app(args);
    app();
  } else if (command == "zx-select") {
    // TODO: Deprecate command in favour of special units?
    ZxSelectApp app(args);
    app();
  } else if (command == "fm") {
    FMApp app(args);
    app();
  } else if (command == "metronome") {
    MetronomeApp app(args.argc, args.argv);
    app();
  } else {
    std::cout << "Unknown command: " << command << "\n";
    return 1;
  }
}
