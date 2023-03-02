#ifndef MIDI_CONTROLLER_H
#define MIDI_CONTROLLER_H

#include <MIDIUSB.h>
#include <Adafruit_MCP23017.h>
#include "InstrumentConfig.h"

class MIDIController {
  public:
    void setup();
    void processMessages();

  private:
    static const int NUM_NOTES = 25;
    static const int START_NOTE = 48;

    Adafruit_MCP23017 mcp;

    // Récupère la broche de sortie correspondant à une note MIDI
    int getOutputPin(int note);

    // Traite les messages MIDI entrants en boucle non bloquante
    static bool notePlaying[NUM_NOTES];
    void processNoteOn(int note);
};

#endif
