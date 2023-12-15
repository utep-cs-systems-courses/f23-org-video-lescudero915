#include <msp430.h>
#include "switches.h"
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"


static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);                          /* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);                         /* if switch down, sense up */
  return p2val;
}

/* setup switch */
void switch_init()
{  
  P2REN |= SWITCHES;                                    /* enables resistors for switches */
  P2IE |= SWITCHES;                                     /* enable interrupts from switches */
  P2OUT |= SWITCHES;                                    /* pull-ups for switches */
  P2DIR &= ~SWITCHES;                                   /* set switches' bits for input */
  
  switch_update_interrupt_sense();
}

void switch_interrupt_handler()
{
    char p2val = switch_update_interrupt_sense();
    if (!(p2val & SW1)) {
        initialMenu();
        set_state(ALTERNATING);
    } else if (!(p2val & SW2)) {
        blinkingMenu();
        set_state(BLINKING);
    } else if (!(p2val & SW3)) {
        jingleMenu();
        set_state(JINGLE);
    } else if (!(p2val & SW4)) {
        mixedMenu();
        set_state(MIXED);                         
    } 

}






