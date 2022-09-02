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

    shared_ptr<Signal<double>> bpm =
        SignalString::parse(args["bpm"].as<string>());
    vector<shared_ptr<Signal<double>>> tracks;
    const vector<string> &patternStrings =
        args.count("pattern") ? args["pattern"].as<vector<string>>()
                              : vector<string>({"10"});

    for (int i = 0; i < patternStrings.size(); ++i) {
      const string &patternStr = patternStrings[i];

      shared_ptr<Sine> osc = make_shared<Sine>();
      osc->frequency << (1 + i) * 500;
      shared_ptr<ControlString> envelope = *ControlString::parse("100ms:1~0");
      shared_ptr<Multiply> attenuator = make_shared<Multiply>();
      attenuator->a << osc;
      attenuator->b << envelope;

      cerr << "Pattern: " << patternStr << "\n";
      shared_ptr<Rhythm> rhythm = Rhythm::parse(patternStr);
      rhythm->bpm << bpm;
      cerr << *rhythm << "\n";
      shared_ptr<Resetter> resetter = make_shared<Resetter>();
      resetter->input << attenuator;
      resetter->trigger << rhythm;

      tracks.push_back(resetter);
    }

    output(*Add::many(tracks));
  }
};
