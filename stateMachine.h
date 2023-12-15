#ifndef stateMachine_included
#define stateMachine_included

typedef enum {
  IDLE,
  ALTERNATING,
  BLINKING,
  JINGLE,
  MIXED
} State;

void set_state(State state);
void advance_state();

#endif
