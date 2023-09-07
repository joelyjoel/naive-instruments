#! /usr/local/bin/bash
echo "$(dirname $0)/checkaudio.sh"
source "$(dirname $0)/checkaudio.sh"

naive osc --pitch 60 --duration 1s > "Sine wave on middle C lasting one second.wav"
checkaudio "Sine wave on middle C lasting one second.wav"

naive osc --waveform saw --pitch 60 --duration 1s > "Sawtooth wave on middle C lasting one second.wav"
checkaudio  "Sawtooth wave on middle C lasting one second.wav"

naive osc --waveform square --pitch 60 --duration 1s > "Square wave on middle C lasting one second.wav"
checkaudio  "Square wave on middle C lasting one second.wav"

naive osc --waveform triangle --pitch 60 --duration 1s > "Triangle wave on middle C lasting one second.wav"
checkaudio  "Triangle wave on middle C lasting one second.wav"

naive osc --waveform saw --pitch 21 --duration 1s > "Bass sawtooth wave.wav"
checkaudio  "Bass sawtooth wave.wav"

naive osc --waveform sine --pitch 108~21 --duration 1s > "Sine sweep accross entire grand piano range.wav"
checkaudio  "Sine sweep accross entire grand piano range.wav"

naive osc --waveform sine --pitch 21~108 --duration 1s > "Upward sine sweep accross entire grand piano range.wav"
checkaudio  "Upward sine sweep accross entire grand piano range.wav"

naive osc --pitch 60 --va 2 --duration 2s > "Middle C Sine wave with Vibrato.wav"
checkaudio  "Middle C Sine wave with Vibrato.wav"

naive boop --duration 1 > "Simple boop.wav"
checkaudio  "Simple boop.wav"

naive boop --duration 5 > "Slightly longer boop.wav"
checkaudio  "Slightly longer boop.wav"

naive boop --duration 1 --waveform triangle > "Trianglular boop.wav"
checkaudio  "Trianglular boop.wav"

naive boop --duration 1 --pitch 50~0 > "Sliding boop.wav"
checkaudio  "Sliding boop.wav"
