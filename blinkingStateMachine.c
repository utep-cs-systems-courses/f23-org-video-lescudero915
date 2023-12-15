#include <msp430.h>
#include "led.h"
#include "lcdutils.h"
#include "lcddraw.h"

static void once_per_second()
{
  static unsigned char number = 0;
  switch (number) {
  case 0:
    toggle_green(0);
    toggle_red(0);
    number = 1;
    break;
  case 1:
    toggle_green(0);
    toggle_red(1);
    number = 2;
    break;
  case 2:
    toggle_green(1);
    toggle_red(0);
    number = 3;
    break;
  case 3:
    toggle_green(1);
    toggle_red(1);
    number = 0;
  }
}

static void update_second()
{
  static unsigned char secondCount = 0;

  if (++secondCount >= 50) {
    secondCount = 0;
    once_per_second();
  }
}


void advance_blinking()
{
  update_second();
}

void reset_blinking()
{
  toggle_green(0);
  toggle_red(0);
}


