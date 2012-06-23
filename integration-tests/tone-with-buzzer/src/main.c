#include <avr/interrupt.h>
#include <avr-tone/avr-tone.h>

/*
 * Test program for the avr-tone library using a buzzer as backend.
 */

// By using the SHORT_BEEPS define, we can have shorter tones for easier simulation
#define BEEP_T 10
#ifdef SHORT_BEEPS
#undef BEEP_T
#define BEEP_T 1
#endif


// frequencies and durations used in the demo song
#define PA 0 //Hz

#define C4 261 //Hz
#define D4 293 //Hz
#define E4 329 //Hz
#define F4_ 369 //Hz
#define G4 391 //Hz
#define A4 440 //Hz
#define B4 493 //Hz

#define C5 523 //Hz
#define D5 587 //Hz
#define E5 659 //Hz
#define F5_ 739 //Hz
#define G5 783 //Hz
#define A5 880 //Hz
#define B5 987 //Hz

#define C6 1046 //Hz

#define QNOTE (80 * BEEP_T) //ms
#define ENOTE (40 * BEEP_T) //ms
#define HNOTE (160 * BEEP_T) //ms


int main(void) {
    initOutput();
    initToneTimer();

    sei();

    // Het Wilhelmus, National Anthem of The Netherlands :)
    while(1) {
        playTone(D4, QNOTE); playTone(G4, QNOTE); playTone(G4, QNOTE); playTone(A4, ENOTE); playTone(B4, ENOTE);
        playTone(C5, ENOTE); playTone(A4, ENOTE); playTone(B4, QNOTE); playTone(A4, ENOTE); playTone(B4, ENOTE);
        playTone(C5, QNOTE); playTone(B4, QNOTE); playTone(A4, ENOTE); playTone(G4, ENOTE); playTone(A4, QNOTE);
        playTone(G4, HNOTE); playTone(PA, QNOTE);

        playTone(D4, QNOTE); playTone(G4, QNOTE); playTone(G4, QNOTE); playTone(A4, ENOTE); playTone(B4, ENOTE);
        playTone(C5, ENOTE); playTone(A4, ENOTE); playTone(B4, QNOTE); playTone(A4, ENOTE); playTone(B4, ENOTE);
        playTone(C5, QNOTE); playTone(B4, QNOTE); playTone(A4, ENOTE); playTone(G4, ENOTE); playTone(A4, QNOTE);
        playTone(G4, HNOTE); playTone(PA, QNOTE);

        playTone(B4, ENOTE); playTone(C5, ENOTE); playTone(D5, HNOTE); playTone(E5, QNOTE); playTone(D5, HNOTE);
        playTone(C5, QNOTE); playTone(B4, QNOTE); playTone(A4, ENOTE); playTone(B4, ENOTE); playTone(C5, QNOTE);
        playTone(B4, QNOTE); playTone(A4, QNOTE); playTone(G4, QNOTE); playTone(A4, HNOTE); playTone(PA, QNOTE);

        playTone(D4, QNOTE); playTone(G4, ENOTE); playTone(F4_, ENOTE); playTone(G4, ENOTE);
        playTone(A4, ENOTE); playTone(B4, QNOTE); playTone(A4, HNOTE); playTone(G4, QNOTE);
        playTone(F4_, QNOTE); playTone(D4, QNOTE); playTone(E4, ENOTE); playTone(F4_, ENOTE);
        playTone(G4, QNOTE); playTone(G4, QNOTE); playTone(F4_, QNOTE); playTone(G4, HNOTE);
        playTone(PA, HNOTE);
    }

    return 0;
}

