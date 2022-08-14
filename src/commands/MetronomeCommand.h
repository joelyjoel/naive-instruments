#include "../lib.h"

class MetronomeCommand : public AudioCommand {

  using AudioCommand::AudioCommand;

  void describeOptions() override {
    describeOutputOptions();
    options.add_options()("bpm,beats-per-minute",
                          po::value<string>()->default_value("139"),
                          "What beats per minute should the metronome play")(
        "pattern", po::value<vector<string>>(), "Binary rhythmic pattern");
  }

  void action() override {

    Signal<double> *bpm = SignalString::parse(args["bpm"].as<string>());
    vector<Signal<double> *> tracks;
    const vector<string> &patternStrings = args["pattern"].as<vector<string>>();

    for (int i = 0; i < patternStrings.size(); ++i) {
      const string &patternStr = patternStrings[i];

      Sine *osc = new Sine;
      osc->frequency << (1 + i) * 500;
      ControlString *envelope = *ControlString::parse("100ms:1~0");
      Multiply *attenuator = new Multiply;
      attenuator->a << osc;
      attenuator->b << envelope;

      cerr << "Pattern: " << patternStr << "\n";
      Rhythm *rhythm = Rhythm::fromBinaryString(patternStr);
      rhythm->bpm << bpm;
      cerr << *rhythm << "\n";
      Resetter *resetter = new Resetter;
      resetter->input << attenuator;
      resetter->trigger << rhythm;

      tracks.push_back(resetter);
    }

    output(*Add::many(tracks));
  }
};
