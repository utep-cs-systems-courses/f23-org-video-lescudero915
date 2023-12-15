#include <msp430.h>
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

static char play_sound;
static int note;
static int delay;

static const Note jingle_bells_notes[] = {
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 100, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 100, 4 },
  { E4, 50, 4 },
  { G4, 50, 4 },
  { C4, 50, 4 },
  { D4, 50, 4 },
  { E4, 250, 4 },
  { F4, 50, 4 },
  { F4, 50, 4 },
  { F4, 100, 4 },
  { F4, 50, 4 },
  { F4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { D4, 50, 4 },
  { D4, 50, 4 },
  { E4, 50, 4 },
  { D4, 50, 4 },
  { G4, 100, 4 },
  { G4, 50, 4 },
  { G4, 50, 4 },
  { G4, 100, 4 },
  { G4, 50, 4 },
  { G4, 50, 4 },
  { G4, 100, 4 },
  { G4, 50, 4 },
  { F4, 50, 4 },
  { E4, 50, 4 },
  { D4, 250, 4 },
  { C4, 50, 4 },
  { C4, 50, 4 },
  { C4, 100, 4 },
  { C4, 50, 4 },
  { D4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { E4, 50, 4 },
  { D4, 50, 4 },
  { D4, 50, 4 },
  { E4, 50, 4 },
  { D4, 50, 4 },
  { G4, 100, 4 },
};

void play_jingle_bells()
{

  if (note < sizeof(jingle_bells_notes) / sizeof(jingle_bells_notes[0])) {
    if (delay <= 0) {
      if (play_sound) {
        play_sound = 0;
        buzzer_set_period(0);
        delay = jingle_bells_notes[note].delay;
        note++;
        updateScreen();

      } else {
        play_sound = 1;
        buzzer_set_period(jingle_bells_notes[note].key);
        delay = jingle_bells_notes[note].duration;
      }
    }

    delay--;
  } else {
    note = 0;
    delay = 0;
    buzzer_set_period(0);
  }
}

void reset_jingle_bells()
{
  play_sound = 0;
  note = 0;
  delay = 0;
  buzzer_set_period(0);
}