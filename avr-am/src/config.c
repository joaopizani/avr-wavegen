#include <avr/io.h>
#include <stdint.h>
#include "config.h"
#include <avr-utils/timers-atmega168.h>


static uint8_t carrier_prescale_bits = 0x0;


void initCarrierTimer(void) {
    TCCR0A |= _BV(WGM01); // clear on compare match
    TIMSK0 |= _BV(OCIE0A); // enable compare match intr.
    carrier_prescale_bits = getTimer0PrescaleBits_atmega168(CARRIER_PRESCALE);
}

void setCarrierFreqKHz(uint16_t f_KHz) {
    const uint16_t carrierTimerPeriodCount = CARRIER_TIMER_FREQ_KHZ / f_KHz;
    const uint8_t carrierTimerToggleCount = (uint8_t) (carrierTimerPeriodCount / 2);
    OCR0A = carrierTimerToggleCount;
}

inline void startCarrierTimer(void) {
    TCCR0B |= carrier_prescale_bits;
}

inline void stopCarrierTimer(void) {
    TCCR0B = 0x00;
}

