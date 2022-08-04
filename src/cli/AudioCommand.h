#include "../core.h"
#include "../file-io/piping.h"
#include "../file-io/record.h"
#include "../parsing/Parse.h"
#include "../playback/BufferedPlayback.h"
#include "Command.h"

class AudioCommand : public Command {
public:
  using Command::Command;

protected:
  void describeOutputOptions() {
    options.add_options()("normalize", "Normalize the audio output")(
        "duration", po::value<std::string>(),
        "Crop the audio output to a certain duration")(
        "output-file,o", po::value<std::string>(),
        "Path to wav file for recording audio\n");
  }

  const Hopefully<std::string> outputFile() {
    if (args.count("output-file"))
      return args["output-file"].as<std::string>();
    else
      return Disappointment;
  }

  float outputDuration() {
    std::string durationStr = args["duration"].as<std::string>();
    return *Parse::interval(durationStr);
  }

protected:
  void output(NaiveInstrument<double> &signal) {
    auto &path = outputFile();
    if (stdoutIsAPipe()) {
      std::cerr << "Piping to stdout\n";
      record(std::cout, signal, outputDuration());
    } else if (!path.success())
      BufferedPlayback::play(signal);
    else {
      record(*path, signal, outputDuration());
      std::cout << *path << "\n";
    }
  }
};
