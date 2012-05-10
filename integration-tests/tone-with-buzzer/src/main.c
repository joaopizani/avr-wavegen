#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr-tone.h>


int main(void) {
    initOutput();
    initToneTimer();

    // start, enable all interrupts
    sei();

    while(1) {
        playTone(440, 1000);
        _delay_ms(1000);
        playTone(650, 1000);
        _delay_ms(1000);
    }

    return 0;
}

