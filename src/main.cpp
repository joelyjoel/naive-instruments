#include "apps/GraphApp.h"
#include "apps/MixApp.h"
#include "apps/OscApp.h"
#include "apps/RandomEnvelopeApp.h"
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
  } else if (command == "slice") {
    SliceApp app(args);
    app.run();
  } else if (command == "graph") {
    GraphApp app(args);
    app.run();
  } else if (command == "ruler") {
    RulerApp app(args);
    app.run();
  } else if (command == "mix") {
    MixApp app(args);
    app.run();
  } else if (command == "osc") {
    OscApp app(args);
    app.run();
  } else if (command == "randvelope") {
    RandomEnvelopeApp app(args);
    app.run();
  } else if (command == "zx-select") {
    // TODO: Deprecate command in favour of special units?
    ZxSelectApp app(args);
    app.run();
  } else {
    std::cout << "Unknown command: " << command << "\n";
    return 1;
  }
}
