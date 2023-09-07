#! /usr/local/bin/bash
source "$(dirname $0)/checkaudio.sh"

naive metronome --bpm 120 --duration 30 > "120bpm metronome.wav"
checkaudio  "120bpm metronome.wav"
