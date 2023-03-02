/**************************************************
    WORK IN PROGRESS     
***********************************************/

systeme concu pour un xylophone de 25 touches.

l'arduino recoit les messages midi par USB et actionne la note selectionnée sur l'instrument a l'aide d'éléctroaimants

Materiel electronique :
*arduino de type leonardo, Micro, Due, Zero etc ...
*2 modules MCP23017 pour ajouter 2x16 sorties
*4 Module ULN2803 pour controller 4 x 8 electroaimants jusqu'a 500mA
*25 electroaimants

librairies:
*MidiUSB.h
*Adafruit_MCP23017.h

--------------------------------------------------------------------------------------------------------
******************************************************************************************************
--------------------------------------------------------------------------------------------------------

System designed for a 25-key xylophone.

The Arduino receives MIDI messages via USB and triggers the selected note on the instrument using electromagnets.

Electronic hardware:
-Arduino Leonardo, Micro, Due, Zero, etc.
-2 MCP23017 modules to add 2x16 outputs.
-4 ULN2803 modules to control 4 x 8 electromagnets up to 500mA.
-25 electromagnets.

Libraries:
-MidiUSB.h
-Adafruit_MCP23017.h
