/*
   Motorcycle alarm: 
   
 The circuit:
 * Analog read in A0 - alarm sensors (resistors/switches)
 * LED connected from digital pin 9 to ground
 * piezzo buzzer connected from digital pin 8 to ground
 * Relays connected from digital pin 7 to ground
 */
const int inpEcho = 13;
const int outTrig = 12;
const int outBuz = 11;
int duration = 0, distance = 0;

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_C8, NOTE_C6, NOTE_FS4,
  NOTE_A3, NOTE_A7, NOTE_A5, NOTE_FS3,
  NOTE_B0, NOTE_B4, NOTE_B2, NOTE_FS1,
  NOTE_B0, NOTE_B4, NOTE_B2, NOTE_FS1,
  NOTE_B0, NOTE_B4, NOTE_B2, NOTE_FS1
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  10, 10, 10, 10
, 10, 10, 10, 10
, 10, 10, 10, 10
, 10, 10, 10, 10
, 10, 10, 10, 10};
  
  
//Mario main theme melody
int mario[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

void underWorl()
{
  int melodyPin = outBuz;
  int size = sizeof(underworld_melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / underworld_tempo[thisNote];
 
    tone(melodyPin, underworld_melody[thisNote], noteDuration);
 
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
 
    // stop the tone playing:
    tone(melodyPin, 0, noteDuration);
  }
}
void playMario() 
{
  int melodyPin = outBuz;
  int size = sizeof(mario) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / tempo[thisNote];
 
    tone(melodyPin, mario[thisNote], noteDuration);
 
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
 
    // stop the tone playing:
    tone(melodyPin, 0, noteDuration);
  }
}

void scan()
{
  digitalWrite(outTrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(outTrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(outTrig, LOW);
  duration = pulseIn(inpEcho, HIGH);
  distance = (duration/2) / 29.1;
}
  
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  // declare pin 9,8,7 to be outputs:
  pinMode(outBuz, OUTPUT);
  
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 3; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(outBuz, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(outBuz);
  }
  // iterate over the notes of the melody:
  for (int thisNote = 3; thisNote < 6; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(outBuz, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(outBuz);
  }
  
  Serial.println("Initted");
  
  
  // radar related 
  pinMode(outTrig, OUTPUT);
  pinMode(inpEcho, INPUT);
}


void loop() {
  
  
  scan();
  
  if (distance >= 150 || distance <= 0) {
    Serial.println("Out of range");
    noTone(outBuz);
  }
  else {
    int intZero=0;
    Serial.print(distance);
    Serial.println(" cm");
    if (distance < 150)
      intZero = 5;
    if (distance < 60)
      intZero = 3;
    if (distance < 30) // if the scan detected sth closer than 30cm the sound is  
      intZero = 0;
      
    for ( int y = 0; y < 2; ++y ) {   
    for ( int x = intZero; x < intZero+4; ++x)
    {
      tone(outBuz, melody[x], 50);
      delay(55);
    }}
    noTone(outBuz);
  }
  
  
  //tone(outBuz, 250, 250);
  delay(250);
}

