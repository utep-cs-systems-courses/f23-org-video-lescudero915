#include <msp430.h>
#include "stateMachine.h"
#include "alternatingStateMachine.h"
#include "blinkingStateMachine.h"
#include "jingleStateMachine.h"
#include "mixedStateMachine.h"
#include "lcdutils.h"
#include "lcddraw.h"

static State current_state;

void set_state(State state)
{
  switch (state) {
  case ALTERNATING:
    if (current_state != ALTERNATING) {
      reset_blinking();
      reset_jingle_bells();
      reset_mixed();
    }
    break;
  case BLINKING:
    if (current_state != BLINKING) {
      reset_alternation();
      reset_jingle_bells();
      reset_mixed();
    }
  case JINGLE:
    if (current_state != JINGLE) {
      reset_alternation();
      reset_blinking();
      reset_mixed();
    }
  case MIXED:
    if (current_state != MIXED) {
      reset_alternation();
      reset_blinking();
      reset_jingle_bells();
    }
  }

  current_state = state;
}

void advance_state()
{
  switch (current_state) {
  case ALTERNATING:
    advance_alternation();
    break;
  case BLINKING:
    advance_blinking();
    break;
  case JINGLE:
    play_jingle_bells();
    break;
  case MIXED:
    advance_mixed();
    break;
  }
}


