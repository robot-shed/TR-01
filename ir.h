// ir.h

// constants related to the specific IR remote used.

// SIRC command codes
// Using the RM-S70
// if two diffrent buttons have the same command code, the device codes are given in the comment
const int irPresetPlus = 16;     // Stop
const int irPresetMinus = 17;    // Reverse
const int irVolumePlus = 18;     // Right
const int irVolumeMinus = 19;    // Decelerate
const int irMuting = 20;         // unused
const int irPower = 21;          // unused
const int irTapePauseA = 25;     // unused
const int irPhono = 32;          // * ignore
const int irTuner = 33;          // Left
const int irVideo = 34;          // Default
const int irTape = 35;           // ignore
const int irCD = 37;             // ignore
const int irPhonoStart = 40;     // unused
const int irPhonoStop = 41;      // unused
const int irDBFB = 49;           // * DBFB = 12 (unused); CD next track = 17 (accelerate)
const int irCDPlay = 50;         // * CD Play = 17 (Max); Tape Play A = 16 (unused)
const int irRewindA = 51;        // unused
const int irFastForwardA = 52;   // unused
const int irRecordA = 54;        // unused
const int irReversePlayA = 55;   // unused
const int irTapeStopA = 56;      // * Tape Stop A = 16 (unused); CD Stop = 17 (forward)
const int irTape2 = 57;          // ignore
const int irDiscSkip = 62;       // unused

//
//   Muting             Power
//
//   Phono     Phono    DBFB
//   Start     Stop
//
//   Tape      Rewind   Fast
//   A/B                Forward
//
//   Reverse   Tape     Record
//   Play      Play
//
//   Disc      Tape     Tape
//   Stop      Stop     Pause
//
//   CD        CD       Next
//   Play      Stop     Track
//
//   Tuner     Preset   Volume
//             +        +
//
//   Video     Preset   Volume
//             -        +
