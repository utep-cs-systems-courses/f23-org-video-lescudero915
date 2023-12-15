#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

int main(void) {
    configureClocks();
    enableWDTInterrupts();
    switch_init();
    led_init();
    buzzer_init();
    lcd_init();
    clearScreen(COLOR_WHITE);
    initialMenu();
    or_sr(0x18);
}

