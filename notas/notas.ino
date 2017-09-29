/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
 #include "pitches.h"

// notes in the melody:
/*
int melody[] = { NOTE_E5, 
                 NOTE_DS5, 
                 NOTE_E5,
                 NOTE_DS5,
                 NOTE_E5,
                 NOTE_B4,
                 NOTE_D5,
                 NOTE_C5
               };
*/
int melody[] = { NOTE_E5,
            NOTE_DS5,
            NOTE_E5,
            NOTE_DS5,
            NOTE_E5,
            NOTE_B4,
            NOTE_D5,
            NOTE_C5,
            NOTE_A4,  
            NOTE_0,
            NOTE_C5,
            NOTE_E5,
            NOTE_A4,
            NOTE_B4,
            NOTE_0,
            NOTE_E5,
            NOTE_A4,
            NOTE_B4,
            NOTE_C5,
            NOTE_0,
            NOTE_0,
            NOTE_E5,
            NOTE_DS5,
            NOTE_E5,
            NOTE_DS5,
            NOTE_E5,
            NOTE_B4,
            NOTE_D5,
            NOTE_C5,
            NOTE_A4
            
            
            };
/*            

e d# e d# e b d c a,
c e a b, e a b c;
e d# e d# e b d c a,
c e a b, e c b a. 
b c d e, g f e d, e e d c, e d c e;
e d# e d# e e d c a, 
c e a b, e a b c;
e d# e d# e b d c a, 
c e a b, e c b a.

*/
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8 };
int length = sizeof(melody) / sizeof(int);
void setup() {

}

void loop() {
  // no need to repeat the melody.
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < length; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    noteDuration = 1000/6;
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }  
  delay(1000);  
  
}
