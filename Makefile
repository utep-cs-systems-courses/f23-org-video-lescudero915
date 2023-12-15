# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf 

#additional rules for files
button.elf: ${COMMON_OBJECTS} buzzer.o main.o switches.o led.o alternatingStateMachine.o stateMachine.o interrupt_handler.o blinkingStateMachine.o jingleStateMachine.o mixedStateMachine.o lcddraw.o lcdutils.o font-11x16.o font-5x7.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: button.elf
	msp430loader.sh  button.elf

clean: $^
	rm -f *.o *.elf

buzzer.c: buzzer.h
switches.c: switches.h
led.c: led.h
alternatingStateMachine.c: alternatingStateMachine.h
stateMachine.c: stateMachine.h 


 

