#!/bin/sh

OPTS="-I./include -mmcu=atmega168p -O1 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -Wstrict-prototypes -DF_CPU=16000000UL -c"

avr-gcc $OPTS src/avrutils/timers-atmega168.c
avr-gcc $OPTS src/avrutils/timers-atmega168p.c
