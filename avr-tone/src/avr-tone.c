#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr-utils/timers-atmega168.h>
#include <avr-alarm/alarm.h>
#include "avr-tone.h"


void initOutput(void) {
    DDRB |= _BV(PB0);
}


void initToneTimer(void) {
    TCCR2A |= _BV(WGM21); // clear on compare match
    TIMSK2 |= _BV(OCIE2A); // enable compare match intr.

    alarm_init();
    alarm_timer_start();
}


inline void startToneTimer(void) {
    TCNT2 = 0x00;
    TCCR2B |= getTimer2PrescaleBits_atmega168(TONE_PRESCALE);
}

inline void stopToneTimer(void) {
    TCCR2B = 0x00;
    PORTB = 0xff;
}

inline void quiet(void) {
    OCR2A = 0x00;
    TCNT2 = 0x00;
}

void setToneFreq(uint16_t f_Hz) {
    const uint32_t toneTimerPeriodCount = TONE_TIMER_FREQ_HZ / f_Hz;
    const uint32_t toneTimerToggleCount = toneTimerPeriodCount >> 1;
    OCR2A = toneTimerToggleCount;
}

void setFreqAlarmHandler(void* freq_uint16_ptr) {
    uint16_t* f_Hz_ptr = (uint16_t*) freq_uint16_ptr;
    uint16_t f_Hz = *f_Hz_ptr; // saving

    if(f_Hz == 0) { // silence
        quiet();
        stopToneTimer();
        // we cannot free the pointer to static variable which stores 0Hz
    } else { // sound
        setToneFreq(f_Hz);
        startToneTimer();
        free(f_Hz_ptr); // we don't need it anymore
        // we cannot free the pointer to static variable which stores 0Hz
    }
}


void playTone(uint16_t f_Hz, uint16_t dur_ms) {
    static uint16_t zero_Hz = 0;
    static uint16_t* zero_Hz_ptr = &zero_Hz;

    uint16_t* f_Hz_ptr = malloc(sizeof(uint16_t));
    *f_Hz_ptr = f_Hz;

    time_ms_t t = alarm_until_last_deadline();
    alarm_insert(t, setFreqAlarmHandler, f_Hz_ptr); // beginning of the sound
    alarm_insert(t + dur_ms, setFreqAlarmHandler, zero_Hz_ptr); // silence thereafter
}

