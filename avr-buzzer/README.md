This module contains one source file (src/toggle.c), which has one interrupt service routine (ISR) that
handles the compare match A interrupt for timer 2 (8-bit timer on atmega168 series). This module is supposed
to be used as a "backend" for tone generation on PORTB, pin 0.  The tone generator configures timer 2 to emit
the TIMER2_COMPA_vect interrupt with the desired frequency, then this module handles the interrupt, toggling
the pin 0 of PORTB.

To compile this module, use the command ./compile.sh. Then you can gather the object files into a static
library (.a) using "avr-ar". If you want to add other files and functions to this module, add them to the
compile.sh script respectively.
