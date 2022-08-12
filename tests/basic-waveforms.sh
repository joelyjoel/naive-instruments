#! /usr/local/bin/bash

naive osc --pitch 60 --duration 1s > "Sine wave on middle C lasting one second.wav"
naive osc --waveform saw --pitch 60 --duration 1s > "Sawtooth wave on middle C lasting one second.wav"
naive osc --waveform square --pitch 60 --duration 1s > "Square wave on middle C lasting one second.wav"
naive osc --waveform triangle --pitch 60 --duration 1s > "Triangle wave on middle C lasting one second.wav"
naive osc --waveform saw --pitch 21 --duration 1s > "Bass sawtooth wave.wav"

naive osc --waveform sine --pitch 108~21 --duration 1s > "Sine sweep accross entire grand piano range.wav"
naive osc --waveform sine --pitch 21~108 --duration 1s > "Upward sine sweep accross entire grand piano range.wav"
naive osc --pitch 60 --va 2 --duration 2s > "Middle C Sine wave with Vibrato.wav"

naive boop --duration 1 > "Simple boop.wav"
naive boop --duration 5 > "Slightly longer boop.wav"
naive boop --duration 1 --waveform triangle > "Trianglular boop.wav"
naive boop --duration 1 --pitch 50~0 > "Sliding boop.wav"
