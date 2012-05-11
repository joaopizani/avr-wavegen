#include <avr/io.h>
#include <stdint.h>
#include "config.h"
#include <timers-atmega168.h>


void initCarrierTimer(void) {
    TCCR0A |= _BV(WGM01); // clear on compare match
    TIMSK0 |= _BV(OCIE0A); // enable compare match intr.
}

void setCarrierFreqKHz(uint16_t f_KHz) {
    const uint16_t carrierTimerPeriodCount = CARRIER_TIMER_FREQ_KHZ / f_KHz;
    const uint8_t carrierTimerToggleCount = (uint8_t) (carrierTimerPeriodCount / 2);
    OCR0A = carrierTimerToggleCount;
}

inline void startCarrierTimer(void) {
    TCCR0B = getTimerPrescaleBits_atmega168(CARRIER_PRESCALE);
}

inline void stopCarrierTimer(void) {
    TCCR0B = 0x00;
}

