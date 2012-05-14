#include <avr/interrupt.h>
#include <config.h>
#include <avr-tone.h>


int main(void) {
    initOutput();
    initToneTimer();
    initCarrierTimer();

    setCarrierFreqKHz(560);

    // start
    sei();

    playTone(440, 50);
    playTone(650, 50);
    playTone(440, 20);

    return 0;
}

