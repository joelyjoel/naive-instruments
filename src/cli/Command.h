#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

using std::cerr;

class Command {

private:
  int argc;
  char **argv;

public:
  Command(int argc, char **argv) : argc(argc), argv(argv) {}

public:
  void run() {
    describeOptions();
    describeHelpOption();
    parseOptions();
    if (args.count("help"))
      showHelp();
    else
      action();
  }

  void operator()() { run(); }

protected:
  virtual void action() {
    cerr << "Oh no, looks like the programmer forgot to oerride the action "
            "method\n";
  }

protected:
  /**
   * Description/declaration of the options in the command.
   */
  po::options_description options;
  virtual void describeOptions() {
    cerr << "Oh no, it looks like the programmer forgot to override e "
            "describeOptions method!\n";
  }

  /**
   * Opt string argument values
   */
  po::variables_map args;

protected:
  void describeHelpOption() { options.add_options()("help", "Show help"); }
  void showHelp() { cerr << options << "\n"; }

private:
  void parseOptions() {
    po::store(po::parse_command_line(argc, argv, options), args);
    po::notify(args);
  }
};
