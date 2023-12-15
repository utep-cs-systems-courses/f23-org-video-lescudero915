#ifndef buzzer_included
#define buzzer_included

// Note frequency defines
#define C4 261   // Middle C
#define D4 293   // D
#define E4 329   // E
#define F4 349   // F
#define G4 392   // G
#define A4 440   // A
#define B4 493   // B

typedef struct {
  short key;
  unsigned short duration;
  unsigned short delay;
} Note;

void buzzer_init();
void buzzer_set_period(short cycles);

#endif
