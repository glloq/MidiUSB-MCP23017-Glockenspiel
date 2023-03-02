#ifndef INSTRUMENT_CONFIG_H
#define INSTRUMENT_CONFIG_H

namespace INSTRUMENT_CONFIG {
  const int NUM_NOTES = 25;
  const int START_NOTE = 48;
  const int NOTE_DURATION_MS = 8;

  const int OUTPUT_PINS[NUM_NOTES] = {
    0, 1, 2, 3, 4,
    5, 6, 7, 8, 9,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
  };
}


#endif
