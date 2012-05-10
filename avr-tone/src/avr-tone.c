#include <avr/io.h>
#include <stdint.h>
#include <timers-atmega168p.h>
#include "avr-tone.h"


void initOutput(void) {
    DDRB |= _BV(PB0);
}

void initToneTimer(void) {
    TCCR2A |= _BV(WGM21); // clear on compare match
    TIMSK2 |= _BV(OCIE2A); // enable compare match intr.
}

inline void startToneTimer(void) {
    TCCR2B = getTimerPrescaleBits_atmega168p(TONE_PRESCALE);
}

inline void stopToneTimer(void) {
    TCCR2B = 0x00;
    PORTB = 0xff;
}

void setToneFreq(uint16_t f_Hz) {
    if(f_Hz == 0) { // silence, so we stop vibrating
        OCR2A = 0x00;
        TCNT2 = 0x00;
        stopToneTimer();
    } else {
        const uint32_t toneTimerPeriodCount = TONE_TIMER_FREQ_HZ / f_Hz;
        const uint32_t toneTimerToggleCount = toneTimerPeriodCount / 2;
        OCR2A = toneTimerToggleCount;
    }
}

/**
 * SOME CALCULATIONS FOR THE DURATION TIMER:
 * 1) Implement it as an alarm mechanism. Which means, have a function that a that sets up an alarm
 * on a certain number of miliseconds, triggering the call of a user-provided handler (function pointer)
 * when the time expires.
 *
 * 2) The playTone(freq, dur) function should be non-blocking. For this to happen, we must have a FIFO of
 * "tone requests", and THE ALARM HANDLER FOR THE NOTE DURATION TIMEOUT is a function that "advances" the
 * queue.
 *
 * 3) The "queue processing function" shall be responsible only for setting the output frequency as
 * requested by playTone. Whenever the queue processing function detects that the queue is empty, silence
 * is played (zero frequency).
 *
 */

void playTone(uint16_t f_Hz, uint16_t dur_ms) {
    long i; //TODO implement FOR REALZ using 16-bit counter

    if(dur_ms != 0) { // if duration is zero do nothing
        setToneFreq(f_Hz);
        startToneTimer();
        for(i = 0; i < 0x001fffff; i++); //TODO implement FOR REALZ using 16-bit cnt.
        stopToneTimer();
    }
}

