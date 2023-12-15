#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "lcdutils.h"
#include "lcddraw.h"


static void update_sound()
{
  static unsigned char highOn = 0;
  if (highOn) {
    highOn = 0;
    buzzer_set_period(1750);
  } else {
    highOn = 1;
    buzzer_set_period(750);
  }
}

static void update_blink()
{
  static unsigned char greenOn = 0;
  
  if (greenOn) {
    greenOn = 0;
    toggle_red(1);
    toggle_green(0);
  } else {
    greenOn = 1;
    toggle_red(0);
    toggle_green(1);
  }
}

static void once_per_second()
{
  update_sound();
  update_blink();
}

static void update_second()
{
  static unsigned char secondCount = 0;
  if (++secondCount >= 250) {
    secondCount = 0;
    once_per_second();
  }
}

void advance_mixed()
{
  update_second();
}

void reset_mixed()
{
  buzzer_set_period(0);
  toggle_green(0);
  toggle_red(0);
}
