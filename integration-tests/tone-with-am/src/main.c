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

// By using the SHORT_BEEPS define, we can have shorter tones for easier simulation
#define BEEP_T 500
#ifdef SHORT_BEEPS
#undef BEEP_T
#define BEEP_T 50
#endif

int main(void) {
    initOutput();
    initToneTimer();
    initCarrierTimer();
    setCarrierFreqKHz(560);

    // long "beep" so that we can notice the scale coming :)
    playTone(1000, (BEEP_T * 2));
    playTone(0, (BEEP_T * 2));

    sei();

    // C major scale, to test that the tones are played in tune :)
    while(1) {
        playTone(C4, BEEP_T); playTone(D4, BEEP_T); playTone(E4, BEEP_T); playTone(F4, BEEP_T);
        playTone(G4, BEEP_T); playTone(A4, BEEP_T); playTone(B4, BEEP_T); playTone(C5, BEEP_T);
        playTone(C5, BEEP_T); playTone(B4, BEEP_T); playTone(A4, BEEP_T); playTone(G4, BEEP_T);
        playTone(F4, BEEP_T); playTone(E4, BEEP_T); playTone(D4, BEEP_T); playTone(C4, BEEP_T);
        playTone(0, (BEEP_T * 2));
        playTone(C5, BEEP_T); playTone(D5, BEEP_T); playTone(E5, BEEP_T); playTone(F5, BEEP_T);
        playTone(G5, BEEP_T); playTone(A5, BEEP_T); playTone(B5, BEEP_T); playTone(C6, BEEP_T);
        playTone(C6, BEEP_T); playTone(B5, BEEP_T); playTone(A5, BEEP_T); playTone(G5, BEEP_T);
        playTone(F5, BEEP_T); playTone(E5, BEEP_T); playTone(D5, BEEP_T); playTone(C5, BEEP_T);
        playTone(0, (BEEP_T * 2));
    }

    return 0;
}

