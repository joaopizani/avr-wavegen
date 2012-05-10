#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr-am/config.h>


ISR(TIMER0_COMPA_vect, ISR_NAKED) {
    // toggle pin 0 of PORTB by writing logical 1 to PINB(0)
    // This will occupy 2 instructions, and the manual says IT WORKS®
    __asm__ __volatile__("sbi 0x03, 0" ::);
    reti();
}

ISR(TIMER2_COMPA_vect) {
    PORTB = 0xff; // carrier LOW
    TCNT0 = 0x00; // clear count (less aliasing)

    if(TCCR0B) stopCarrierTimer();
    else startCarrierTimer();
}

