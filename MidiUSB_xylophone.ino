#include <MIDIUSB.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>

// Définition des broches des MCP23017
#define MCP1_ADDRESS 0x20
#define MCP2_ADDRESS 0x21
Adafruit_MCP23017 mcp1, mcp2;
//*************************************************************************************************************//
//**************                     Partie Reglages de l'instrument                          *****************//
//*************************************************************************************************************//
// Définition de la configuration de l'instrument
#define INSTRUMENT_START_NOTE 60 // Do central
#define INSTRUMENT_RANGE 25 // 2 octaves et 1 note
//le temps ou l'electroaimant restera actif mis par defaut a 50ms
const int timeHit[INSTRUMENT_RANGE] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
// Définition des broches des électroaimants utilisé => si vous ne les utilisez pas dans l'ordre a vous de voir ;)
const int magnetPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, // 1er mcp
                           16, 17, 18, 19, 20, 21, 22, 23, 24};                 // 2nd mcp
//***************************************************************************************************************//
// Définition des variables pour la gestion des notes
bool notePlaying[INSTRUMENT_RANGE] = {false};
unsigned long noteStartTime[INSTRUMENT_RANGE] = {0};

// Fonction pour activer l'électroaimant correspondant à une note donnée
void turnOnMagnet(int note) {
  if (note >= INSTRUMENT_START_NOTE && note < INSTRUMENT_START_NOTE + INSTRUMENT_RANGE) {
    int magnetIndex = note - INSTRUMENT_START_NOTE;
    if (magnetIndex >= 0 && magnetIndex < sizeof(magnetPins)) {
      if (magnetIndex < 16) {
        mcp1.digitalWrite(magnetPins[magnetIndex], HIGH);
      } else {
        mcp2.digitalWrite(magnetPins[magnetIndex - 16], HIGH);
      }
    }
  }
}

// Fonction pour désactiver l'électroaimant correspondant à une note donnée
void turnOffMagnet(int note) {
  if (note >= INSTRUMENT_START_NOTE && note < INSTRUMENT_START_NOTE + INSTRUMENT_RANGE) {
    int magnetIndex = note - INSTRUMENT_START_NOTE;
    if (magnetIndex >= 0 && magnetIndex < sizeof(magnetPins)) {
      if (magnetIndex < 16) {
        mcp1.digitalWrite(magnetPins[magnetIndex], LOW);
      } else {
        mcp2.digitalWrite(magnetPins[magnetIndex - 16], LOW);
      }
    }
  }
}

// Fonction pour jouer une note
void playNote(int note) {
  if (note >= INSTRUMENT_START_NOTE && note < INSTRUMENT_START_NOTE + INSTRUMENT_RANGE) {
    int noteIndex = note - INSTRUMENT_START_NOTE;
    if (!notePlaying[noteIndex]) {
      notePlaying[noteIndex] = true;
      noteStartTime[noteIndex] = millis();
      turnOnMagnet(note);
    }
  }
}

// Fonction d'interruption pour jouer les notes en cours
void timerInterrupt() {
  for (int i = 0; i < INSTRUMENT_RANGE; i++) {
    if (notePlaying[i]) {
      unsigned long elapsedTime = millis() - noteStartTime[i];
      if (elapsedTime > timeHit[i]) {
        notePlaying[i] = false;
        turnOffMagnet(INSTRUMENT_START_NOTE + i);
      }
    }
  }
}

// Fonction pour traiter les messages MIDI entrants
void handleMidiMessage() {
  midiEventPacket_t midiPacket = MidiUSB.read();
  if (midiPacket.header == 0x9) {
    int note = midiPacket.byte1;
int velocity = midiPacket.byte2;
if (velocity > 0) {
  playNote(note);
} else {
  int noteIndex = note - INSTRUMENT_START_NOTE;
  notePlaying[noteIndex] = false;
  turnOffMagnet(note);
}
}
}

void setup() {
// Initialisation des MCP23017
mcp1.begin(MCP1_ADDRESS);
mcp2.begin(MCP2_ADDRESS);
for (int i = 0; i < sizeof(magnetPins); i++) {
if (i < 16) {
mcp1.pinMode(magnetPins[i], OUTPUT);
mcp1.digitalWrite(magnetPins[i], LOW);
} else {
mcp2.pinMode(magnetPins[i - 16], OUTPUT);
mcp2.digitalWrite(magnetPins[i - 16], LOW);
}
}

// Initialisation de l'interruption matérielle
noInterrupts();
TCCR1A = 0;
TCCR1B = 0;
TCNT1 = 0;
OCR1A = 15624; // 1s / (prescaler * (1/16Mhz)) - 1
TCCR1B |= (1 << WGM12);
TCCR1B |= (1 << CS12) | (1 << CS10);
TIMSK1 |= (1 << OCIE1A);
interrupts();
}

void loop() {
handleMidiMessage();
}

// Fonction d'interruption pour le timer
ISR(TIMER1_COMPA_vect) {
timerInterrupt();
}
