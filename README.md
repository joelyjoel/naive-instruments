# Naive Instruments

This is an audio library, its my naive attempt to implement an audio library to
calm myself down while I'm in an anxiety state. I'm not really thinking about 
performance, just about what makes sense to me. That's why its naive.

It aims to be a command line application for editing & processing audio signals.

## Installation
 
At the moment, the makefile is only set up to build for Mac OS.

You will need [boost](https://www.boost.org)!

```bash
brew install boost
```

Compile it:

```bash
make
```

Add the `bin/` directory [to your path](https://linuxize.com/post/how-to-add-directory-to-path-in-linux/).

.bashrc

```bash
PATH=$PATH:~/path/to/this/repo/bin
```


## How add a new command

To create a new command you need do two things:

  1. Create a new class (probably a subclass of `AudioCommand`) in
     `src/commands/<your-command's-name>.h`

  2. register the command in `src/main.cpp`

Here's an example of a very simple command:

```cpp
// src/commands/NoiseCommand.h

// The first thing we do here is to include the library, to make all the
// classes available:
#include "../lib.h"

// Next we declare a class which extends the `AudioCommand` base class. This
// has helpful methods for command line options, audio input/output from
// streams and sending audio to the speakers.
class NoiseCommand : public AudioCommand {
public:
  // We have to manually add the class constructor from the base class. This is
  // some boilerplate code that I hope to eliminate the need for soon.
  using AudioCommand::AudioCommand;

protected:
  // By overriding the `describeOptions` we declare how the user may configure
  // this command using optstrings.
  //
  // Helpful video about command line tools:
  // https://www.youtube.com/watch?v=kgII-YWo3Zw&t=1225s
  void describeOptions() override {

    // This helpful method sets up the standard options used by the `output`
    // method later on. Allows the user to use the `-o <output-file>.wav` to
    // send audio to a file, or pipe the WAV output to stdout.
    describeOutputOptions();
  }

protected:
  // We define the actual signal processing part of our command by overriding
  // the `action` method.
  void action() override {

    // Create a `Noise` signal (a subclass of `Signal` which outputs white noise
    Noise noise;

    // We send our signal straight to the output. The `output` method will work
    // out where to send the audio depending on the user's command line options.
    output(noise);
  }
};
```

For more examples see the files in `src/commands`

## Control Signal shorthand

PLEASE NOTE: I'm kinda planning to change this a lot soon based on what I've learnt from using it for a while. Watch this space..

You may use a shorthand for control signals. These are made out of a sequence 
of time-steps.

Use `_` to indicate that the signal should remain static for one step.

Use `~` to indicate that the signal should be gliding toward the next value for 
a step.

Use a number to set the value of a step.

Use a colon `:` for tempo indication.

(Maybe,) use `±` for lfo vibrato?


### Examples

Start at `440Hz` for 4 steps, then switch (instantly) to 550Hz
```
440Hz____550Hz____
```

Start at `1` and glide to `0` over 4 seconds

```
1s: 1~~~~0
```

Frequency signal for Twinkle Twinkle Little Star

```
120bpm:
c_ c_ g_ g_ a_ a_ g__  
f_ f_ e_ e_ d_ d_ c__
```


