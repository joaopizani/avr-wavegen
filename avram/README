This module contains two source files (src/avr-am/config.c and src/avr-am/toggle.c), and is responsible for
providing an Amplitude Modulation (AM) "backend" for the tone generation library. The "config.c" file has
functions to help setup a carrier wave with desired frequency, by working with timer 0. Then the file toggle.c
has two interrupt service routines (ISRs):

 - The first routine (TIMER0_COMPA_vect) is activated with twice the desired frequency of the carrier. Thus,
   each time this ISR is called, we just toggle pin 0 of PORTB (one instruction).

 - The second routine (TIMER2_COMPA_vect) is to be called with twice the frequency defined by the TONE
   LIBRARY. Thus, with this routine we turn TIMER0 on and off, effectively modulating the carrier in a
   square fashion (multiplying it by 0 and 1).

To compile this module, use the command ./compile.sh. Then you can gather the object files into a static
library (.a) using "avr-ar". If you want to add other files and functions to this module, add them to the
compile.sh script respectively.
