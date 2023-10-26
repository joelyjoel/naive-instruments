# Naive Instruments

A naive approach to audio signal processing. 

This repository provides a C++ library for audio synthesis and musical composition. It can be used via a C++ API, or via an interactive command line interface.

I'm writing this to satisfy my curiosity about signal processing, to teach myself C++ and to demonstrate where I'm at with that to people I'd like to work with. As a result, potential users (and even potential use-cases) have taken a back seat. If you are looking for a well-supported C++ audio library to use in your project maybe try [JUCE](https://juce.com) or [Open Frameworks](https://openframeworks.cc).

## Structure of the library.

[The most important file](src/signal/Signal.h) in the library defines the base class for signal processing. Signals behave as iterators over frames, and a signal may read one or more other signals as inputs. In this way complex graph-like structures may be assembled to perform modular synthesis, analysis or other processes.

Many overrides of the `Signal<frame>` base class are provided to perform various operations on signals. These classes are called [Signal Processes](./src/signal/signal-processes.h). See the [guide to writing signal processes](#how-to-add-a-new-signal-process)

Because assembling instances of signal process classes is quite verbose, a library of shorthand functions is provided under the `SignalShorthands` namespace. These deal with standard library smart-pointers to signal process classes. 

```cpp
using namespace NaiveInstrument::SignalShorthands;

// Create a simple 440Hz sawtooth wave using a signal shorthand.
mono sawtoothWave = saw(440);

// Create a more complex signal, summing together multiple sine
// waves. Operator overloads are also provided by the signal 
// shorthand library.
mono harmonics = sine(100) + sine(200) * .75 + sine(300) * .5 + sine(400) * .25;

```

The command line interface is composed by a series of subcommands which are found in the `src/commands` directory. See the [guide for writing audio commands](#how-to-add-a-new-command-to-the-command-line-interface) for more details.

## Deprecated code

This library has been a learning curve, and so there are some parts of it which have been reimplemented with the wisdom of hindsight. I'm trying to cut dependency on the older/jankier classes, but its taken time because its boring work. 

The precursor to the `Signal` base template, was a similar but more complex class called `FrameStream`. These worked very similarly, but in a more convoluted way.

### Design faults

Spelling out the current flaws & limitations may help to show the way for future development.

 - 👎 So far the signal processes all process one sample at a time, which is inefficient. While the core of the library could support chunked audio processing if it were added, this hasn't been done yet.
 - 👎 The order of events in signal graphs is recalculated every frame.
 - 👎 Some reference tone tests which run inside Catch2 never make any assertion. (The assertion happens later when the reference tone checksums are compared).
 - 👎 CMake is being used incorrectly, it seems to be creating bad artefacts
 - 👎 Makefile is being used as a test runner
 - 👎 Broadly, everything is implemented within header files. `.cpp` files are barely used.
 - 👎 Large portions of deprecated code still live on as dependencies of commands that have yet to be updated.

## Installation

For now only Mac OS is supported. Although the library should work on other platforms too with a little encouragement. The best up-to-date record of dependencies and installation process is the GitHub workflow for running tests.

You will need [boost](https://www.boost.org)

```bash
brew install boost
```

Compile it:

```bash
make
```

Optionally, run the tests:

```bash
make test
```

Add the `bin/` directory [to your path](https://linuxize.com/post/how-to-add-directory-to-path-in-linux/).

.bashrc

```bash
PATH=$PATH:~/path/to/this/repo/bin
```

To run the tests you will need ffmpeg:

```bash
brew install ffmpeg
```



## How to add a new signal process

1. Create a class that overrides the `Signal<Frame>` base class

```cpp
#include "src/signal/Signal.h"

/**
 * Adds two signals together.
 */
class Sum : public Signal<double> {
	// ...
};
```

Here, the template parameter `double` specifies that each frame of the signal is a double-precision float. As such the signal will process one frame at a time.


2. Add `SignalReader`s as member properties to define the inputs to your signal process

```cpp
class Sum : public Signal<double> {
public:
	SignalReader<double> input1{this};
	SignalReader<double> input2{this};
	
	// ...
};
```

3. Override the `action` method to define the behaviour of your process. The action method reads inputs, performs calculations, updates internal state, and - most importantly of all - updates the `output` field of the signal process.

4. Optionally, override the `init()` method which is called only once before the signal starts. By default, the `init()` method just calls `action()`.
5. Create a shorthand function in the `SignalShorthands` namespace to quickly & conveniently create a smart pointer to your signal process. 

```cpp
namespace SignalShorthands {

mono sum(mono a, mono b) {
	auto ptr = std::make_shared<Sum>();
	ptr->input1 = a;
	ptr->input2 = b;
	return ptr;
}

}
```

6. Write at least one test that uses 

## How to write tests for this project

Audio signals contain a lot of data and their most important characteristics require a human ear to assess. This makes test-writing for audio projects tricky. The current solution is a work in progress.

All tests can be run at once using `make test` and they are also ran by a GitHub workflow whenever a Pull Request is created onto `main`.

There are two types of tests: 

 - C++ unit tests written using the Catch2 framework (these use the extension `.test.cpp` and a found through out the project next to the modules they are checking.)

 - End-to-end command line scripts for testing the command line interface to this library. These are found in the `tests/` directory and use the extension `.test.sh`.

The end-to-end tests produce audio files which are written to the `reference-tones/` directory. Any change at all to the audio data in this directory is registered as a test failure and must be re-approved by a human audition. When the tests find a reference tone that hasn't been seen before the use will be prompted interactively to check that the new file sounds correct.

I've found it expedient though unsatisfactory to write audio files to the `reference-tones/` directory from the C++ unit tests sometimes. This piggy backs of the end-to-end tests to enforce a human audition of audio artefacts that aren't accessible by the command line API.

## How to add a new command to the command line interface

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