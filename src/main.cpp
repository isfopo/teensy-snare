#include <Arduino.h>
#include <hellodrum.h>

#define MIDI_CHANNEL 0

byte SNARE[9] = {
    100, // sensitivity (1-100)
    10,  // threshold (1-100)
    5,   // scan time (1-100)
    40,  // mask time (1-100)
    20,  // rim sensitivity (1-100)
    10,  // rim threshold (1-100)
    3,   // curve type (0-4)
    38,  // note (0-127)
    37,  // note of rim (0-127)
};

HelloDrum snare(15, 14);

void setup()
{
  snare.setCurve(SNARE[6]);
}

void loop()
{
  snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[4], SNARE[5]);

  if (snare.hit == true)
  {
    usbMIDI.sendNoteOn(SNARE[7], snare.velocity, MIDI_CHANNEL);
    usbMIDI.sendNoteOff(SNARE[7], 0, MIDI_CHANNEL);
  }
  else if (snare.hitRim == true)
  {
    usbMIDI.sendNoteOn(SNARE[8], snare.velocity, MIDI_CHANNEL);
    usbMIDI.sendNoteOff(SNARE[8], 0, MIDI_CHANNEL);
  }
}
