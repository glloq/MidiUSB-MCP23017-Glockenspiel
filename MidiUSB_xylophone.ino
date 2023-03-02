#include <MIDIUSB.h>
#include <Adafruit_MCP23017.h>
#include "MIDIController.h"

MIDIController midiController;

void setup() {
  // Initialise le contrôleur MIDI et l'instrument
  midiController.setup();
}

void loop() {
  // Traite les messages MIDI entrants
  midiController.processMessages();
}
