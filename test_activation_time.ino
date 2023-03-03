/**********************************************************************************************************************************************************
ce code est juste fait pour tester le temps d'activation necessaire des electroaimants (pendant les reglages a la configuration de votre instrument)
viens demander le temps en ms depuis le moniteur serie de l'IDE d'arduino et actionne tout les electroaimants l'un après l'autre avec de temps renseigné
*********************************************************************************************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP23017.h>

// Définition des broches des MCP23017
#define MCP1_ADDRESS 0x20
#define MCP2_ADDRESS 0x21
Adafruit_MCP23017 mcp1, mcp2;

#define INSTRUMENT_RANGE 25 //nombe de notes a tester
// Définition des broches des électroaimants
const int magnetPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

void activateMagnet(int magnetIndex, int time) {
  if (magnetIndex >= 0 && magnetIndex < sizeof(magnetPins)) {
    if (magnetIndex < 16) {
      mcp1.digitalWrite(magnetPins[magnetIndex], HIGH);
    } else {
      mcp2.digitalWrite(magnetPins[magnetIndex - 16], HIGH);
    }
    delay(time);
    if (magnetIndex < 16) {
      mcp1.digitalWrite(magnetPins[magnetIndex], LOW);
    } else {
      mcp2.digitalWrite(magnetPins[magnetIndex - 16], LOW);
    }
  }
}

void testMagnetActivationTime(int time) {
  for (int i = 0; i < INSTRUMENT_RANGE; i++) {
    activateMagnet(i, time);
    delay(500); //temps entre chaque note
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

  Serial.begin(9600);
  while (!Serial) {}

  Serial.println("Test de temps d'activation des électroaimants");
  Serial.println("Entrez le temps d'activation en ms :");
}

void loop() {
  if (Serial.available() > 0) {
    int time = Serial.parseInt();
    if (time > 0) {
      Serial.print("Temps d'activation : ");
      Serial.print(time);
      Serial.println(" ms");
      Serial.println("Début du test...");
      testMagnetActivationTime(time);
      Serial.println("Fin du test.");
      Serial.println("Entrez le temps d'activation en ms :");
    } else {
      Serial.println("Temps invalide, veuillez réessayer.");
      Serial.println("Entrez le temps d'activation en ms :");
    }
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
