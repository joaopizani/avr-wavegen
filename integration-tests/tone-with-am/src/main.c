#include <avr/interrupt.h>
#include <avr-am/config.h>
#include <avr-tone/avr-tone.h>


int main(void) {
    initOutput();
    initToneTimer();
    initCarrierTimer();

    setCarrierFreqKHz(560);

    // start
    sei();

    playTone(440, 500);
    playTone(650, 500);
    playTone(440, 500);
    playTone(650, 500);

    // since now playback is asynchronous, we must have an "event loop" here :)
    while(1);

    return 0;
}

