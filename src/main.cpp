#include "apps/FilterApp.h"
#include "apps/GraphApp.h"
#include "apps/MixApp.h"
#include "apps/NoiseApp.h"
#include "apps/OscApp.h"
#include "apps/RandomApp.h"
#include "apps/RulerApp.h"
#include "apps/SliceApp.h"
#include "apps/ZxSelectApp.h"
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
  } else if (command == "slice")
    SliceApp(args).run();
  else if (command == "graph")
    GraphApp(args).run();
  else if (command == "ruler")
    RulerApp(args).run();
  else if (command == "mix")
    MixApp(args).run();
  else if (command == "osc")
    OscApp(args).run();
  else if (command == "filter")
    FilterApp(args).run();
  else if (command == "noise")
    NoiseApp(args).run();
  else if (command == "random")
    RandomApp(args).run();
  else if (command == "zx-select")
    // TODO: Deprecate command in favour of special units?
    ZxSelectApp(args).run();
  else {
    std::cout << "Unknown command: " << command << "\n";
    return 1;
  }
}
