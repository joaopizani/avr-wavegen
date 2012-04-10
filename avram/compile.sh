#!/bin/sh

OPTS="-I./include -I../avrutils/include -mmcu=atmega168p -O1 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -Wstrict-prototypes -DF_CPU=16000000UL -c"

avr-gcc $OPTS src/avram/config.c
avr-gcc $OPTS src/avram/toggle.c
