enum Unit {
  unknownUnit = -1,
  noUnit = 0,

  // Time
  second = 100,
  millisecond,
  minute,
  hour,
  crotchet,
  smp,
  zeroCrossing,

  // Frequency
  Hz = 200,
  bpm,
  /** Midi pitch number */
  midi,

  // Interval
  octave,
  semitone,

  // Volume
  dB,

};
