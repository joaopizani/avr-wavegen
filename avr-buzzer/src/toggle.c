#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER2_COMPA_vect, ISR_NAKED) {
    // toggle pin 0 of PORTB by writing logical 1 to PINB(0)
    __asm__ __volatile__("sbi 0x03, 0" ::);
    reti();
}

