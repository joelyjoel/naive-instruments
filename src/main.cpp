#include "./lib.h"
#include <string>

int main(int argc, char **argv) {
  MainArgs args(argc, argv + 2);

  if (argc == 1) {
    std::cout << "Naive Instruments CLI.\n";
    return 0;
  }

  std::string command = argv[1];
  if (command == "help") {
    std::cout << "No help has been written yet!\n";
    return 0;
  } else {
    std::cout << "Unknown command: " << command << "\n";
    return 1;
  }
}
