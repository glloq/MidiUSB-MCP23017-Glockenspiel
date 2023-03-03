Ce projet consiste en la création d'un instrument MIDI contrôlé par des messages MIDI à l'aide d'un microcontrôleur Arduino Leonardo. 

L'instrument est un xylophone composé de 25 électroaimants, contrôlés par deux MCP23017 via la communication I2C. 
Lorsqu'un message MIDI est reçu, il est analysé pour déterminer la note à jouer, et la fonction playNote est appelée pour activer l'électroaimant correspondant. 

La fonction turnOnMagnet est utilisée pour activer la sortie numérique correspondante via la bibliothèque MCP23017. 
La fonction turnOffMagnet est appelée après un délai pour désactiver l'électroaimant et arrêter la note. 

Une interruption matérielle est utilisée pour gérer la temporisation et jouer les notes plus rapidement. 

Le code est écrit de manière modulaire, ce qui facilite sa modification et son extension.

## Matériel nécessaire

   - Arduino Leonardo ou compatible
   - Xylophone avec 25 électroaimants
   - 2 MCP23017
   - 4 ULN2803 ou ULN2804 en fonction des electroaimants choisi (500Ma contre 1A max)
   - Câble USB pour connecter l'Arduino à l'ordinateur
   - Les câbles pour connecter les differents composants

## Bibliothèques utilisées

  -  Adafruit_MCP23017 (pour contrôler les MCP23017 en I2C)
  -  MIDIUSB (pour la communication MIDI via USB)

## Configuration de l'instrument

Pour modifier la note de départ, le nombre de notes que l'instrument peut jouer et le temps pendant lequel l'électroaimant doit rester actif avant d'être désactivé. Il faut adapter la partie du code encadré a votre utilisation.

## Utilisation

   - Connectez l'Arduino au xylophone et aux MCP23017 à l'aide des câbles.
   - Connectez l'Arduino à l'ordinateur à l'aide du câble USB.
   - Téléversez le code sur l'Arduino à l'aide de l'IDE Arduino.
   - Lancez un logiciel de production musicale ou un séquenceur MIDI sur votre ordinateur.
   - Configurez le logiciel pour utiliser l'Arduino comme périphérique MIDI.
   - Jouez de la musique sur le logiciel et les notes seront transmises à l'Arduino pour activer les électroaimants correspondants sur le xylophone.
