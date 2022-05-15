#pragma once

#include "NaiveInstrument.h"
#include "WavReader.h"
#include "record.h"
#include <filesystem>
#include <fstream>
#include <iostream>

class AudioSnapshotTest {
  const std::string &testName;
  const std::string testOutputDirectory = "test-outputs/";
  const std::string snapshotsDirectory = "snapshots/";
  const std::string snapshotPath;
  const std::string testOutputPath;
  NaiveInstrument<double> &signal;
  const float duration;

public:
  AudioSnapshotTest(const std::string &testName,
                    NaiveInstrument<double> &signal, float duration = 1)
      : testName(testName), signal(signal), duration(duration),
        snapshotPath(snapshotsDirectory + testName + ".wav"),
        testOutputPath(testOutputDirectory + testName + ".wav") {

    run();
  }

  AudioSnapshotTest(const std::string &testName,
                    NaiveInstrument<double> *signal, float duration = 1)
      : AudioSnapshotTest(testName, *signal, duration) {}

public:
  void run() {
    createDirectoriesIfDontExist();
    if (snapshotExists()) {
      recordTestTone();
      std::cout << "Comparing " << testOutputPath << " to " << snapshotPath
                << "\n";
      if (compareAudioFiles(testOutputPath, snapshotPath))
        pass();
      else
        fail();

    } else {
      recordSnapshot();
    }
  }

private:
  void recordTestTone() { record(testOutputPath, signal, duration); }

private:
  void recordSnapshot() {
    record(snapshotPath, signal, duration);
    std::cout << "Recorded snapshot for test '" << testName << "' into '"
              << snapshotPath << "'. Please audition it before committing.\n";
  }

private:
  bool snapshotExists() { return std::filesystem::exists(snapshotPath); }

private:
  void pass() { std::cout << "Test Passed: " << testName << "\n"; }

private:
  void fail() {
    std::cout << "Test failed: " << testName << "\n";
    throw 1;
  }

private:
  static bool compareAudioFiles(const std::string actualWavPath,
                                const std::string expectedWavPath) {

    WavReader actualWav(actualWavPath);
    WavReader expectedWav(expectedWavPath);

    if (actualWav.numberOfFrames() != expectedWav.numberOfFrames()) {
      std::cout << "Audio file durations don't match: expected "
                << expectedWav.numberOfFrames() << ", got "
                << actualWav.numberOfFrames() << ".\n";
      return false;
    }

    int numberOfFrames = actualWav.numberOfFrames();

    for (int frameIndex = 0; frameIndex < numberOfFrames; ++frameIndex) {
      auto aFrame = actualWav.readNextFrame();
      auto bFrame = expectedWav.readNextFrame();

      if (aFrame.left == bFrame.left && aFrame.right == bFrame.right)
        continue;
      else {
        std::cout << "Audio files don't match at frame " << frameIndex << "\n";
        return false;
      }
    }

    return true;
  }

  void createDirectoriesIfDontExist() {
    if (!std::filesystem::exists(snapshotsDirectory))
      std::filesystem::create_directory(snapshotsDirectory);
    if (!std::filesystem::exists(testOutputDirectory))
      std::filesystem::create_directory(testOutputDirectory);
  }
};
