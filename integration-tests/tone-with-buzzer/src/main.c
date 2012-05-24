#include <avr/interrupt.h>
#include <avr-tone/avr-tone.h>


int main(void) {
    initOutput();
    initToneTimer();

    playTone(440, 50);
    playTone(880, 50);
    playTone(440, 50);
    playTone(880, 50);

    // start, enable all interrupts
    sei();

    // since now playback is asynchronous, we must have an "event loop" here :)
    while(1);

    return 0;
}

