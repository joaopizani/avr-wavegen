#include <avr/interrupt.h>
#include <avr-tone.h>
#include <alarm.h>


int main(void) {
    initOutput();
    initToneTimer();

    // start, enable all interrupts
    sei();

    playTone(440, 50);
    playTone(650, 70);

    // since now playback is asynchronous, we must have an "event loop" here :)
    while(1);

    return 0;
}

