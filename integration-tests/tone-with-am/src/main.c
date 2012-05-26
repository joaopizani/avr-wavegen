#include <avr/interrupt.h>
#include <avr-am/config.h>
#include <avr-tone/avr-tone.h>

#include <util/delay.h>

#define C4 261 //Hz
#define D4 293 //Hz
#define E4 329 //Hz
#define F4 349 //Hz
#define G4 391 //Hz
#define A4 440 //Hz
#define B4 493 //Hz

#define C5 523 //Hz
#define D5 587 //Hz
#define E5 659 //Hz
#define F5 698 //Hz
#define G5 783 //Hz
#define A5 880 //Hz
#define B5 987 //Hz

#define C6 1046 //Hz


/*
 * Test program for the avr-tone library using AM as backend.
 * Synchronization between producer of tones (user thread) and consumer
 * (interrupt context) is - as of now - done manually. That's the reason
 * for the _delay_ms(t) you see in the code...
 */


int main(void) {
    initOutput();
    initToneTimer();
    initCarrierTimer();
    setCarrierFreqKHz(560);

    // init "beeps" so that we can notice the scale coming :)
    int i;
    for(i = 0; i < 5; i++) {
        playTone(1000, 100);
        playTone(0, 900);
    }
    playTone(1000, 1000);
    playTone(0, 1000);


    sei();
    _delay_ms(7000);

    // C major scale, to test that the tones are played in tune :)
    while(1) {
        playTone(C4, 1000); playTone(D4, 1000); playTone(E4, 1000); playTone(F4, 1000);
        playTone(G4, 1000); playTone(A4, 1000); playTone(B4, 1000); playTone(C5, 1000);
        playTone(C5, 1000); playTone(B4, 1000); playTone(A4, 1000); playTone(G4, 1000);
        playTone(F4, 1000); playTone(E4, 1000); playTone(D4, 1000); playTone(C4, 1000);
        playTone(0, 1000);
        _delay_ms(7000);
        playTone(C5, 1000); playTone(D5, 1000); playTone(E5, 1000); playTone(F5, 1000);
        playTone(G5, 1000); playTone(A5, 1000); playTone(B5, 1000); playTone(C6, 1000);
        playTone(C6, 1000); playTone(B5, 1000); playTone(A5, 1000); playTone(G5, 1000);
        playTone(F5, 1000); playTone(E5, 1000); playTone(D5, 1000); playTone(C5, 1000);
        playTone(0, 1000);
        _delay_ms(7000);
    }

    return 0;
}

