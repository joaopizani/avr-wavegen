#!/bin/sh

OPTS="-mmcu=atmega168p -O2 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -Wstrict-prototypes -DF_CPU=16000000UL -c"

avr-gcc $OPTS src/toggle.c
