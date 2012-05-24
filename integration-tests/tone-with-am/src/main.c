#include <avr/interrupt.h>
#include <avr-am/config.h>
#include <avr-tone/avr-tone.h>


int main(void) {
    initOutput();
    initToneTimer();
    initCarrierTimer();

    setCarrierFreqKHz(560);

    playTone(440, 50);
    playTone(650, 50);
    playTone(440, 50);
    playTone(650, 50);

    // start
    sei();

    // since now playback is asynchronous, we must have an "event loop" here :)
    while(1);

    return 0;
}

