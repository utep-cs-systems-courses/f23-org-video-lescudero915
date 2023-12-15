#include <msp430.h>
#include "led.h"
#include "lcdutils.h"
#include "lcddraw.h"

static unsigned char greenBlinkLimit = 0;
static unsigned char redBlinkLimit = 8;


static void update_blink()
{
  static unsigned char greenBlinkCount = 0;
  static unsigned char redBlinkCount = 0;

  if (++greenBlinkCount >= greenBlinkLimit) {
    greenBlinkCount = 0;
    toggle_green(1);
  } else {
    toggle_green(0);
  }

  if (++redBlinkCount >= redBlinkLimit) {
    redBlinkCount = 0;
    toggle_red(1);
  } else {
    toggle_red(0);
  }
}

static void once_per_second()
{
  if (++greenBlinkLimit >= 8) {
    greenBlinkLimit = 0;
  }

  if (--redBlinkLimit <= 0) {
    redBlinkLimit = 8;
  }
}

static void update_second()
{
  static unsigned char secondCount = 0;

  if (++secondCount >= 250) {
    secondCount = 0;
    once_per_second();
  }
}

void advance_alternation()
{
  update_blink();
  update_second();
}

void reset_alternation()
{
  toggle_green(0);
  toggle_red(0);
}
