#! bin/bash

naive fm 60 2 --1to0 24 --duration 2 > "Simple FM tone.wav"

naive fm 100ms:90~40~~~30~~20\ 1s:~10 40 --1to0 50ms:30~0 --0-out 1~~0 --duration  2.5 > "FM Kick.wav"
