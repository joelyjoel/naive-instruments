#include "apps/GraphApp.h"
#include "apps/SliceApp.h"
#include "lib.h"
#include <string>

int main(int argc, char **argv) {
  MainArgs args(argc - 1, argv + 1);

  if (argc == 1) {
    // TODO: use class FrontPage : public App
    std::cout << "Naive Instruments CLI.\n";
    return 0;
  }

  // TODO: Migrate getch-log as `ni graph -i`
  // TODO: Migrate rms-graph as `ni graph`
  // TODO: Migrate ruler as `ni ruler`
  // TODO: Migrate zero crossing utils as units in the sample interface
  // TODO: Migrate relentless-tone as `ni osc`

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
  } else {
    std::cout << "Unknown command: " << command << "\n";
    return 1;
  }
}
