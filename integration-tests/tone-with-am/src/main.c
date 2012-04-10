#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avram/config.h>
#include <avrtone.h>


int main(void) {
    initOutput();
    initToneTimer();
    initCarrierTimer();

    setCarrierFreqKHz(560);

    // start
    sei();

    while(1) {
        playTone(440, 1000);
        _delay_ms(300);
        playTone(650, 1000);
    }

    return 0;
}

