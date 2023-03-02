#include "MIDIController.h"

bool MIDIController::notePlaying[NUM_NOTES] = {false};

void MIDIController::setup() {
  // Initialise le module de contrôle des sorties
  mcp.begin();
  for (int i = 0; i < NUM_NOTES; i++) {
    mcp.pinMode(INSTRUMENT_CONFIG::OUTPUT_PINS[i], OUTPUT);
    mcp.digitalWrite(INSTRUMENT_CONFIG::OUTPUT_PINS[i], LOW);
  }

  // Initialise les variables de suivi des notes jouées
  for (int i = 0; i < NUM_NOTES; i++) {
    notePlaying[i] = false;
  }
}

void MIDIController::processMessages() {
  // Traite les messages MIDI entrants en boucle non bloquante
  while (MidiUSB.available()) {
    midiEventPacket_t event = MidiUSB.read();
    if (event.header == 0x09) {
      // NoteOn message
      processNoteOn(event.byte1);
    }
  }
}

void MIDIController::processNoteOn(int note) {
  if (!notePlaying[note - START_NOTE]) {
    // Joue la note si elle n'est pas déjà en train d'être jouée
    notePlaying[note - START_NOTE] = true;

    // Active la sortie correspondant à la note pendant la durée de frappe configurée
    int outputPin = getOutputPin(note);
    mcp.digitalWrite(outputPin, HIGH);
    delay(INSTRUMENT_CONFIG::NOTE_DURATION_MS);
    mcp.digitalWrite(outputPin, LOW);

    // Marque la note comme arrêtée
    notePlaying[note - START_NOTE] = false;
  }
}

int MIDIController::getOutputPin(int note) {
  // Récupère la broche de sortie correspondant à une note MIDI
  int index = note - START_NOTE;
  return INSTRUMENT_CONFIG::OUTPUT_PINS[index];
}
