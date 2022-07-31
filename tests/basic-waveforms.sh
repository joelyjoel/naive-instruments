#! /usr/local/bin/bash

ni osc --pitch 60 --duration 1s > "Sine wave on middle C lasting one second.wav"
ni osc --waveform saw --pitch 60 --duration 1s > "Sawtooth wave on middle C lasting one second.wav"
ni osc --waveform square --pitch 60 --duration 1s > "Square wave on middle C lasting one second.wav"
ni osc --waveform triangle --pitch 60 --duration 1s > "Triangle wave on middle C lasting one second.wav"
